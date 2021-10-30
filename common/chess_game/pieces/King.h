#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position);

  char getDrawing() const override;
};

#endif  // KING_H_
