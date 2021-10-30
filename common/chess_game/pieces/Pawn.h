#ifndef PAWN_H_
#define PAWN_H_

#include <chess_game/Piece.h>

class Pawn : public Piece {
 public:
  Pawn(PieceColor color, Position position);

  char getDrawing() const override;

 private:
  std::list<std::pair<int, int>> getPossibleBeamMoves() const override;

  std::list<std::pair<int, int>> getPossibleStepMoves() const override;
};

#endif  // PAWN_H_
