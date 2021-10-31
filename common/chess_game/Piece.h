#ifndef PIECE_H_
#define PIECE_H_

#include <list>
#include "Position.h"
#include "Drawable.h"

enum PieceColor { WHITE, BLACK };

class Piece : public Drawable {
 public:
  Piece(PieceColor color, Position position);

  Position getPosition() const;

  void move(Position position);

  std::list<Position> getPossiblePositions() const;

  virtual ~Piece() = default;

 protected:
  PieceColor color_;
  bool has_moved_;

  virtual std::list<std::pair<int, int>> getVectorBeamMoves() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves() const = 0;

 private:
  Position position_;
  std::list<Position> getPossibleStepPositions() const;
  std::list<Position> getPossibleBeamPositions() const;
};

#endif  // PIECE_H_
