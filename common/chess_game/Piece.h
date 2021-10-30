#ifndef PIECE_H_
#define PIECE_H_

#include <Drawable.h>
#include "Position.h"

enum PieceColor {WHITE, BLACK};

class Piece : public Drawable {
 public:
  Piece(PieceColor color, Position position, char drawing);

  Position getPosition() const;

  char getDrawing() const override;

  void move(Position position);

 private:
  PieceColor color_;
  Position position_;
  char drawing_;
};

#endif  // PIECE_H_
