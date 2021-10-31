#ifndef QUEEN_H_
#define QUEEN_H_

#include <chess_game/Piece.h>

class Queen : public Piece {
 public:
  Queen(PieceColor color, Position position);

  char getDrawing() const override;
 protected:
  std::list<std::pair<int, int>> getVectorBeamMoves() const override;
  std::list<std::pair<int, int>> getVectorStepMoves() const override;
};

#endif  // QUEEN_H_
