#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <chess_game/Piece.h>

class Knight : public Piece {
 public:
  Knight(PieceColor color, Position position);

  char getDrawing() const override;
};

#endif  // KNIGHT_H_
