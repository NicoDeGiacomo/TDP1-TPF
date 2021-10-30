#ifndef ROOK_H_
#define ROOK_H_

#include <chess_game/Piece.h>

class Rook : public Piece {
 public:
  Rook(PieceColor color, Position position);
};

#endif  // ROOK_H_
