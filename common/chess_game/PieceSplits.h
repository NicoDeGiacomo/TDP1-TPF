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

 private:
  Node* root_;
  std::list<Node*> nodes_;

  Node *findNode_(Piece *piece);
  void removeFromBoard_(Piece *piece);
  void appendToBoard_(Piece *piece);
  bool addProbability_(Node *node, float probability);
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
