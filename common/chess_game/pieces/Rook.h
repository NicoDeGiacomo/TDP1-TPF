#ifndef ROOK_H_
#define ROOK_H_

#include <chess_game/Piece.h>

class Rook : public Piece {
 public:
  Rook(PieceColor color, Position position, Board* board);

 private:
  Rook(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;
};

#endif  // ROOK_H_
