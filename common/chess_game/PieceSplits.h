#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_

#include "Piece.h"

struct Node;
class Piece;

class PieceSplits {
 public:
  PieceSplits(Piece* piece);
  virtual ~PieceSplits();

  void addSplit(Piece* piece, Piece* split1, Piece* split2);

  void removeSplit(Piece* piece);

  void mergeSplits(Piece* piece, Piece* with);

  bool contains(const Piece* piece) const;

 private:
  Node* root_;
  std::list<Node*> nodes_;

  Node *findNode_(const Piece *piece) const;
  void removeFromBoard_(Piece *piece);
  void appendToBoard_(Piece *piece);
  bool propagateProbability_(Node *node, float probability);
  static bool _areBrothers(Node *node1, Node *node2);
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
