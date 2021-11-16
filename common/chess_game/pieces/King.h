#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position, Board* board);
  char getDrawing() const override;

  void eat() override;

 private:
  King(PieceColor color, Position position, Board* board, PieceSplits* splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
};

#endif  // KING_H_
