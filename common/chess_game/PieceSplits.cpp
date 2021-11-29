#include <stdexcept>
#include <algorithm>
#include "PieceSplits.h"

struct SplitNode_ {
  Piece* piece;
  float probability;
  std::shared_ptr<SplitNode_> left;
  std::shared_ptr<SplitNode_> right;
  std::weak_ptr<SplitNode_> father;
  Piece* entanglement;
  bool leaf;

  explicit SplitNode_(Piece *piece)
      : piece(piece),
        probability(1.0f),
        left(nullptr),
        right(nullptr),
        father(),
        entanglement(nullptr),
        leaf(true) {}

  SplitNode_(Piece *piece, const std::shared_ptr<SplitNode_>& father)
      : piece(piece),
        probability(father->probability / 2),
        left(nullptr),
        right(nullptr),
        father(father),
        entanglement(nullptr),
        leaf(true) {}

  ~SplitNode_() = default;
};

PieceSplits::PieceSplits(Piece* piece) : root_(std::make_shared<SplitNode_>(piece)) {
}

void PieceSplits::addSplit(Piece* piece, Piece* split1, Piece* split2) {
    std::shared_ptr<SplitNode_> father = findNode_(piece);
    if (father == nullptr || !father->leaf) {
        throw std::invalid_argument("Invalid action.");
    }

    father->left = std::make_shared<SplitNode_>(split1, father);
    father->right = std::make_shared<SplitNode_>(split2, father);
    split1->appendToBoard_();
    split2->appendToBoard_();

    father->leaf = false;
    father->piece = nullptr;
    piece->removeFromBoard_();
    delete piece;
}

void PieceSplits::removeSplit(Piece* piece) {
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    if (node == nullptr || !node->leaf) {
        throw std::invalid_argument("Invalid action.");
    }

    piece->removeFromBoard_();
    std::shared_ptr<SplitNode_> father = node->father.lock();
    if (father->right == node) {
        father->right = nullptr;
    }
    if (father->left == node) {
        father->left = nullptr;
    }
    propagateProbability_(father, node->probability);

    delete piece;
}

void PieceSplits::mergeSplits(Piece *piece, Piece *with) {
    std::shared_ptr<SplitNode_> node1 = findNode_(piece);
    std::shared_ptr<SplitNode_> node2 = findNode_(with);
    if (node1 == nullptr || node2 == nullptr || !node1->leaf || !node2->leaf) {
        throw std::invalid_argument("Invalid move: split not found.");
    }

    if (!areBrothers_(node1, node2) && !areBrothers_(node1->father.lock(),
                                                     node2)
        && !areBrothers_(node1, node2->father.lock())) {
        throw std::invalid_argument("Invalid move: non mergeable splits.");
    }

    with->removeFromBoard_();
    std::shared_ptr<SplitNode_> father = node2->father.lock();
    if (father->right == node2) {
        father->right = nullptr;
    }
    if (father->left == node2) {
        father->left = nullptr;
    }
    propagateProbability_(node1, node2->probability);

    delete with;
}

void PieceSplits::addEntanglement(Piece* piece, Piece* with) {
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    node->entanglement = with;
}

bool PieceSplits::contains(const Piece* piece) const {
    return findNode_(piece) != nullptr;
}

float PieceSplits::getProbability(const Piece *piece) const {
    return findNode_(piece)->probability;
}

void PieceSplits::setProbability(Piece *piece, float probability) {
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    if (node) {
        node->probability = probability;
    }
}

void PieceSplits::confirmSplit(Piece *piece) {
    removeAllSplits_(root_, piece);
    piece->resetSplits_();
}

void PieceSplits::confirmEntanglement(Piece *piece) {
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    if (node && node->entanglement) {
        node->entanglement->denySplit_();
    }
}

void PieceSplits::denyEntanglement(Piece *piece) {
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    if (node && node->entanglement) {
        node->entanglement->confirmSplit_();
    }
}

void PieceSplits::removeAllSplits_(const std::shared_ptr<SplitNode_> &node,
                                   Piece *piece) {
    if (node->leaf && node->piece != piece) {
        node->piece->removeFromBoard_();
        delete node->piece;
        return;
    }
    if (node->left) {
        removeAllSplits_(node->left, piece);
    }
    if (node->right) {
        removeAllSplits_(node->right, piece);
    }
}

std::shared_ptr<SplitNode_> PieceSplits::findNode_(const Piece *piece) const {
    return findNode_(root_, piece);
}

std::shared_ptr<SplitNode_> PieceSplits::findNode_(const std::shared_ptr<SplitNode_> &node, const Piece *piece) const {
    if (node->piece == piece) {
        return node;
    }

    if (node->left) {
        std::shared_ptr<SplitNode_> found = findNode_(node->left, piece);
        if (found) {
            return found;
        }
    }
    if (node->right) {
        std::shared_ptr<SplitNode_> found = findNode_(node->right, piece);
        if (found) {
            return found;
        }
    }

    return nullptr;
}
bool PieceSplits::propagateProbability_(const std::shared_ptr<SplitNode_>& node, float probability) {
    if (node->leaf) {
        node->probability += probability;
        if (node->probability >= 1.0f) {
            node->piece->resetSplits_();
            return true;
        }
    } else {
        if(!node->left && !node->right) {
            return propagateProbability_(node->father.lock(), probability / 2);
        }
    }

    if (node->left && node->right) {
        return propagateProbability_(node->left, probability / 2)
            || propagateProbability_(node->right, probability / 2);
    }
    if (node->left) {
        return propagateProbability_(node->left, probability);
    }
    if (node->right) {
        return propagateProbability_(node->right, probability);
    }

    return false;
}

bool PieceSplits::areBrothers_(const std::shared_ptr<SplitNode_>& node1, const std::shared_ptr<SplitNode_>& node2) {
    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }

    if (node1->father.lock() != node2->father.lock()) {
        return false;
    }

    return true;
}

std::list<Position> PieceSplits::getEntanglements(const Piece *piece) const {
    std::list<Position> positions;
    std::shared_ptr<SplitNode_> node = findNode_(piece);
    if (node && node->entanglement) {
        positions.push_back(node->entanglement->getPosition());
    }

    return positions;
}
