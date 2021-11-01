#ifndef BISHOP_H_
#define BISHOP_H_

#include <chess_game/Piece.h>

class Bishop : public Piece {
 public:
  Bishop(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 private:
  std::list<std::pair<int, int>> getVectorBeamMoves() const override;
  std::list<std::pair<int, int>> getVectorStepMoves() const override;
};

#endif  // BISHOP_H_
