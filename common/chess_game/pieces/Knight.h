#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <chess_game/Piece.h>

class Knight : public Piece {
 public:
  Knight(PieceColor color, Position position, Board* board);
  char getDrawing() const override;

 private:
  Knight(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
};

#endif  // KNIGHT_H_
