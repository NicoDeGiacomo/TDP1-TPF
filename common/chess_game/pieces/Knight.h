#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <chess_game/Piece.h>

class Knight : public Piece {
 public:
  Knight(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 protected:
  Knight(PieceColor color, Position position, Board* board, float probability);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  void createSplit_(Position to, float probability) override;
};

#endif  // KNIGHT_H_
