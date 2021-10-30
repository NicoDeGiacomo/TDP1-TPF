#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <chess_game/Piece.h>

class Knight : public Piece {
 public:
  Knight(PieceColor color, Position position);

  char getDrawing() const override;

 protected:
  std::list<std::pair<int, int>> getPossibleBeamMoves() const override;
  std::list<std::pair<int, int>> getPossibleStepMoves() const override;
};

#endif  // KNIGHT_H_
