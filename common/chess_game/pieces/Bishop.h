#ifndef BISHOP_H_
#define BISHOP_H_

#include <chess_game/Piece.h>

class Bishop : public Piece {
 public:
  Bishop(PieceColor color, Position position, Board* board);


 private:
  Bishop(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
};

#endif  // BISHOP_H_
