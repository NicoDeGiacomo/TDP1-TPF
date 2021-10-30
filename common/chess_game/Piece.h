#ifndef PIECE_H_
#define PIECE_H_

#include "Position.h"

enum PieceColor {WHITE, BLACK};

class Piece {
  PieceColor color_;
  Position position_;

 public:
  Piece(PieceColor color, Position position);
};

#endif  // PIECE_H_
