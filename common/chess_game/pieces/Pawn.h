#ifndef PAWN_H_
#define PAWN_H_

#include <Piece.h>

class Pawn : public Piece {
 public:
  Pawn(PieceColor color, Position position, Board* board);


 private:
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
  void validateMerge_() override;
  void move_(Position position, bool merge) override;
};

#endif  // PAWN_H_
