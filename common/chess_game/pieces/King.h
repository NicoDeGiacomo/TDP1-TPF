#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position);

  char getDrawing() const override;
 protected:
  std::list<std::pair<int, int>> getPossibleBeamMoves() const override;
  std::list<std::pair<int, int>> getPossibleStepMoves() const override;
};

#endif  // KING_H_
