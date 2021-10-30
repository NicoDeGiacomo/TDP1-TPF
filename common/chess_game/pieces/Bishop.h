#ifndef BISHOP_H_
#define BISHOP_H_

#include <chess_game/Piece.h>

class Bishop : public Piece {
 public:
  Bishop(PieceColor color, Position position);

  char getDrawing() const override;
 protected:
  std::list<std::pair<int, int>> getPossibleBeamMoves() const override;
  std::list<std::pair<int, int>> getPossibleStepMoves() const override;
};

#endif  // BISHOP_H_
