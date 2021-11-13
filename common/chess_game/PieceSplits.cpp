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
    : root_(new Node(piece)), nodes_() {}

void PieceSplits::addSplit(Piece *piece, Piece *split1, Piece *split2) {
    Node* node = findNode_(piece);
    if (node == nullptr) {
        throw std::invalid_argument("Invalid action.");
    }

    node->left = new Node(split1, node);
    node->right = new Node(split2, node);
    nodes_.push_back(node->left);
    nodes_.push_back(node->right);
    appendToBoard_(split1);
    appendToBoard_(split2);

    node->father->show = false;
    removeFromBoard_(node->father->piece);
}

void PieceSplits::removeSplit(Piece *piece) {
    Node* node = findNode_(piece);
    if (node == nullptr) {
        throw std::invalid_argument("Invalid action.");
    }

    if (node->father == root_) {

    }

    Node* father = node->father;
    if (father->right == node) {
        father->right = nullptr;
        if (father->left != nullptr) {
            addProbability_(father->left, node->piece->probability_);
        }
    } else if (father->left == node) {
        father->left = nullptr;
        if (father->right != nullptr) {
            addProbability_(father->right, node->piece->probability_);
        }
    }

    if (node->show) {
        node->show = false;
        removeFromBoard_(piece);
    }
    nodes_.remove(node);
    delete node;

    if (father->right == nullptr && father->left == nullptr) {
        removeSplit(father->piece);
    }
}

Node *PieceSplits::findNode_(Piece *piece) {
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

bool PieceSplits::addProbability_(Node *node, float probability) {
    node->piece->probability_ += probability;
    if (node->piece->probability_ == 1.0f && node->show) {
        node->piece->finishMeasure_();
        return true;
    }

    if (node->left && node->right) {
        return addProbability_(node->left, probability / 2)
            || addProbability_(node->right, probability / 2);
    }
    if (node->left) {
        return addProbability_(node->left, probability);
    }
    if (node->right) {
        return addProbability_(node->right, probability);
    }

    return false;
}

PieceSplits::~PieceSplits() {
    for (auto node : nodes_) {
        delete node;
    }
}
