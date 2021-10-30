#ifndef QUEEN_H_
#define QUEEN_H_

#include <chess_game/Piece.h>

class Queen : public Piece {
 public:
  Queen(PieceColor color, Position position);

  char getDrawing() const override;
};

#endif  // QUEEN_H_
