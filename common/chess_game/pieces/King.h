#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

  void eat() override;

 protected:
  std::list<std::pair<int, int>> getVectorBeamMoves() const override;
  std::list<std::pair<int, int>> getVectorStepMoves() const override;
};

#endif  // KING_H_
