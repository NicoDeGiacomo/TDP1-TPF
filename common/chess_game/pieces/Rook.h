#ifndef ROOK_H_
#define ROOK_H_

#include <chess_game/Piece.h>

class Rook : public Piece {
 public:
  Rook(PieceColor color, Position position);

  char getDrawing() const override;

 private:
  std::list<std::pair<int, int>> getVectorBeamMoves() const override;
  std::list<std::pair<int, int>> getVectorStepMoves() const override;
};

#endif  // ROOK_H_
