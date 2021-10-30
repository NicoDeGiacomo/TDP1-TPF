#ifndef PAWN_H_
#define PAWN_H_

#include <chess_game/Piece.h>

class Pawn : public Piece {
 public:
  Pawn(PieceColor color, Position position);
};

#endif  // PAWN_H_
