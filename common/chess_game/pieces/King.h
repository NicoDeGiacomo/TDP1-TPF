#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

  void eat() override;

 protected:
  King(PieceColor color, Position position, Board* board, float probability);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  void createSplit_(Position to, float probability) override;
};

#endif  // KING_H_
