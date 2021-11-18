#include <stdexcept>
#include <algorithm>
#include "PieceSplits.h"

struct SplitNode_ {
  Piece* piece;
  float probability;
  std::shared_ptr<SplitNode_> left;
  std::shared_ptr<SplitNode_> right;
  std::weak_ptr<SplitNode_> father;
  bool leaf;

  explicit SplitNode_(Piece *piece)
      : piece(piece),
        probability(1.0f),
        left(nullptr),
        right(nullptr),
        father(),
        leaf(true) {}

  SplitNode_(Piece *piece, const std::shared_ptr<SplitNode_>& father)
      : piece(piece),
        probability(father->probability / 2),
        left(nullptr),
        right(nullptr),
        father(father),
        leaf(true) {}

  ~SplitNode_() = default;
};

PieceSplits::PieceSplits(Piece* piece) : nodes_() {
    nodes_.push_back(std::make_shared<SplitNode_>(piece));
}

void PieceSplits::addSplit(Piece* piece, Piece* split1, Piece* split2) {
    std::shared_ptr<SplitNode_> father = findNode_(piece);
    if (father == nullptr || !father->leaf) {
        throw std::invalid_argument("Invalid action.");
    }

    father->left = std::make_shared<SplitNode_>(split1, father);
    father->right = std::make_shared<SplitNode_>(split2, father);
    nodes_.push_back(father->left);
    nodes_.push_back(father->right);
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

    nodes_.remove(node);
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

    if (!_areBrothers(node1, node2) && !_areBrothers(node1->father.lock(), node2)
        && !_areBrothers(node1, node2->father.lock())) {
        throw std::invalid_argument("Invalid move: non mergeable splits.");
    }

    with->removeFromBoard_();
    nodes_.remove(node2);
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

void PieceSplits::removeAllSplits() {
    deletePiecesRecursive_(nodes_.front());
}

std::shared_ptr<SplitNode_> PieceSplits::findNode_(const Piece *piece) const {
    for (const auto& node : nodes_) {
        if (node->piece == piece) {
            return node;
        }
    }
    return nullptr;
}

bool PieceSplits::propagateProbability_(const std::shared_ptr<SplitNode_>& node, float probability) {
    if (node->leaf) {
        node->probability += probability;
        if (node->probability >= 1.0f) {
            node->piece->finishMeasure_();
            return true;
        }
    } else {
        if(!node->left && !node->right) {
            nodes_.remove(node);
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

bool PieceSplits::contains(const Piece* piece) const {
    return findNode_(piece) != nullptr;
}

bool PieceSplits::_areBrothers(const std::shared_ptr<SplitNode_>& node1, const std::shared_ptr<SplitNode_>& node2) {
    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }

    if (node1->father.lock() != node2->father.lock()) {
        return false;
    }

    return true;
}

float PieceSplits::getProbability(const Piece *piece) const {
    return findNode_(piece)->probability;
}

void PieceSplits::deletePiecesRecursive_(const std::shared_ptr<SplitNode_>& node) {
    if (node->leaf) {
        node->piece->removeFromBoard_();
        delete node->piece;
    }
    if (node->left) {
        deletePiecesRecursive_(node->left);
    }
    if (node->right) {
        deletePiecesRecursive_(node->right);
    }
}
