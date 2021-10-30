#ifndef BISHOP_H_
#define BISHOP_H_

#include <chess_game/Piece.h>

class Bishop : public Piece {
 public:
  Bishop(PieceColor color, Position position);
};

#endif  // BISHOP_H_
