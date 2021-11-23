#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_

#include "Piece.h"

struct SplitNode_;
class Piece;

class PieceSplits {
 public:
  PieceSplits(Piece* piece);

  virtual ~PieceSplits() = default;

  void addSplit(Piece* piece, Piece* split1, Piece* split2);

  void removeSplit(Piece* piece);

  void mergeSplits(Piece* piece, Piece* with);

  bool contains(const Piece* piece) const;

  float getProbability(const Piece* piece) const;

  void confirmSplit(Piece *piece);

 private:
  std::shared_ptr<SplitNode_> root_;

  void removeAllSplits_(const std::shared_ptr<SplitNode_> &node,
                        Piece *piece);
  std::shared_ptr<SplitNode_> findNode_(const Piece *piece) const;
  std::shared_ptr<SplitNode_> findNode_(const std::shared_ptr<SplitNode_>& node, const Piece *piece) const;
  bool propagateProbability_(const std::shared_ptr<SplitNode_>& node, float probability);
  static bool areBrothers_(const std::shared_ptr<SplitNode_>& node1, const std::shared_ptr<SplitNode_>& node2);
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_PIECESPLITS_H_
