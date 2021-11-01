#ifndef PIECE_H_
#define PIECE_H_

#include <list>
#include "Position.h"
#include "Drawable.h"
#include "Board.h"

class Board;
enum class PieceColor { WHITE, BLACK };

class Piece : public Drawable {
 public:
  Piece(PieceColor color, Position position, Board* board);

  Position getPosition() const;

  void move(Position position);

  std::list<Position> getPossibleMoves() const;

  virtual ~Piece() = default;

 protected:
  Position position_;
  PieceColor color_;
  bool has_moved_;
  Board* board_;

  virtual std::list<std::pair<int, int>> getVectorBeamMoves() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves() const = 0;
  Piece* getPieceFromBoard(Position &position) const;

 private:
  std::list<Position> getPossibleStepPositions_() const;
  std::list<Position> getPossibleBeamPositions_() const;
};

#endif  // PIECE_H_
