#ifndef PAWN_H_
#define PAWN_H_

#include <chess_game/Piece.h>

class Pawn : public Piece {
 public:
  Pawn(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 private:
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
  void merge_() override;
};

#endif  // PAWN_H_
