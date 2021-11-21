#ifndef KING_H_
#define KING_H_

#include <chess_game/Piece.h>

class King : public Piece {
 public:
  King(PieceColor color, Position position, Board* board);

  void eat() override;

 private:
  King(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
};

#endif  // KING_H_
