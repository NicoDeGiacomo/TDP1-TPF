#ifndef ROOK_H_
#define ROOK_H_

#include <chess_game/Piece.h>

class Rook : public Piece {
 public:
  Rook(PieceColor color, Position position, Board* board);

  char getDrawing() const override;

 private:
  Rook(PieceColor color, Position position, Board* board, float probability);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  void createSplit_(Position to, float probability) override;
};

#endif  // ROOK_H_
