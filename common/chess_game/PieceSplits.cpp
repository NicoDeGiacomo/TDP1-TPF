#include <stdexcept>
#include <algorithm>
#include "PieceSplits.h"

struct Node {
  Piece* piece;
  struct Node* left;
  struct Node* right;
  struct Node* father;
  bool show;

  explicit Node(Piece *piece)
      : piece(piece),
        left(nullptr),
        right(nullptr),
        father(nullptr),
        show(true) {}

  Node(Piece *piece, Node *father)
      : piece(piece),
        left(nullptr),
        right(nullptr),
        father(father),
        show(true) {}
};

PieceSplits::PieceSplits(Piece *piece)
    : root_(new Node(piece)), nodes_() {
    nodes_.push_back(root_);
}

void PieceSplits::addSplit(Piece *piece, Piece *split1, Piece *split2) {
    Node* node = findNode_(piece);
    if (node == nullptr || !node->show) {
        throw std::invalid_argument("Invalid action.");
    }

    split1->probability_ = piece->probability_ / 2;
    split2->probability_ = piece->probability_ / 2;
    node->left = new Node(split1, node);
    node->right = new Node(split2, node);
    nodes_.push_back(node->left);
    nodes_.push_back(node->right);
    appendToBoard_(split1);
    appendToBoard_(split2);

    node->show = false;
    removeFromBoard_(node->piece);
}

void PieceSplits::removeSplit(Piece *piece) {
    Node* node = findNode_(piece);
    if (node == nullptr) {
        throw std::invalid_argument("Invalid action.");
    }

    Node* father = node->father;
    if (father->right == node) {
        father->right = nullptr;
        if (father->left != nullptr) {
            if (propagateProbability_(father->left, node->piece->probability_)) {
                return;
            }
        }
    } else if (father->left == node) {
        father->left = nullptr;
        if (father->right != nullptr) {
            if (propagateProbability_(father->right, node->piece->probability_)) {
                return;
            }
        }
    }

    if (node->show) {
        node->show = false;
        removeFromBoard_(piece);
        delete piece;  // todo check
    }
    nodes_.remove(node);
    delete node;

    if (father->right == nullptr && father->left == nullptr) {
        removeSplit(father->piece);
    }
}

void PieceSplits::mergeSplits(Piece *piece, Piece *with) {
    Node* node1 = findNode_(piece);
    Node* node2 = findNode_(with);
    if (node1 == nullptr || node2 == nullptr || !node1->show || !node2->show) {
        throw std::invalid_argument("Invalid move: split not found.");
    }

    if (!_areBrothers(node1, node2) && !_areBrothers(node1->father, node2)
        && !_areBrothers(node1, node2->father)) {
        throw std::invalid_argument("Invalid move: non mergeable splits.");
    }

    if (propagateProbability_(node1, node2->piece->probability_)) {
        piece->removeFromBoardAndDelete_(with);
        return;
    }
    node2->piece->probability_ = 0;
    removeSplit(node2->piece);
    piece->removeFromBoard_(with);
}

Node *PieceSplits::findNode_(const Piece *piece) const {
    for (auto* node : nodes_) {
        if (node->piece == piece) {
            return node;
        }
    }
    return nullptr;
}

void PieceSplits::removeFromBoard_(Piece *piece) {
    root_->piece->removeFromBoard_(piece);
}

void PieceSplits::appendToBoard_(Piece *piece) {
    root_->piece->appendToBoard_(piece);
}

bool PieceSplits::propagateProbability_(Node *node, float probability) {
    node->piece->probability_ += probability;
    if (node->piece->probability_ == 1.0f && node->show) {
        node->piece->finishMeasure_();
        return true;
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

PieceSplits::~PieceSplits() {
    for (auto node : nodes_) {
        delete node;
    }
}

bool PieceSplits::contains(const Piece *piece) const {
    return findNode_(piece) != nullptr;
}

bool PieceSplits::_areBrothers(Node *node1, Node *node2) {
    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }

    if (node1->father != node2->father) {
        return false;
    }

    return true;
}
