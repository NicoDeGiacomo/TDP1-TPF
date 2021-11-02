#ifndef QUEEN_H_
#define QUEEN_H_

#include <chess_game/Piece.h>

class Queen : public Piece {
 public:
  Queen(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 protected:
  Queen(PieceColor color, Position position, Board* board, float probability);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  void createSplit_(Position to, float probability) override;

};

#endif  // QUEEN_H_
