#ifndef PIECE_H_
#define PIECE_H_

#include <list>
#include "Position.h"
#include "Drawable.h"

enum PieceColor {WHITE, BLACK};

class Piece : public Drawable {
 public:
  Piece(PieceColor color, Position position);

  Position getPosition() const;

  void move(Position position);

  std::list<Position> getPossibleMoves() const;

  virtual ~Piece() = default;

 private:
  PieceColor color_;
  Position position_;
  std::list<Position> move_multiple_;
  std::list<Position> move_once_;
};

#endif  // PIECE_H_
