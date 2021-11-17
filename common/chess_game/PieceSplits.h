#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_

#include "Piece.h"

struct SplitNode_;
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
  SplitNode_* root_;
  std::list<SplitNode_*> nodes_;

  SplitNode_ *findNode_(const Piece *piece) const;
  void removeFromBoard_(Piece *piece);
  void appendToBoard_(Piece *piece);
  bool propagateProbability_(SplitNode_ *node, float probability);
  static bool _areBrothers(SplitNode_ *node1, SplitNode_ *node2);
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
