#ifndef QUEEN_H_
#define QUEEN_H_

#include <chess_game/Piece.h>

class Queen : public Piece {
 public:
  Queen(PieceColor color, Position position, Board* board);
  char getDrawing() const override;

 private:
    const char PIECE_KEY = 'q';
  Queen(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  std::list<std::pair<int, int>> getVectorBeamMoves_() const override;
  std::list<std::pair<int, int>> getVectorStepMoves_() const override;
  Piece * createSplit_(Position to) override;

};

#endif  // QUEEN_H_
