#ifndef BISHOP_H_
#define BISHOP_H_

#include <chess_game/Piece.h>

class Bishop : public Piece {
 public:
  Bishop(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 private:
  Bishop(PieceColor color, Position position, Board* board, float probability);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  void createSplit_(Position to, float probability) override;
};

#endif  // BISHOP_H_
