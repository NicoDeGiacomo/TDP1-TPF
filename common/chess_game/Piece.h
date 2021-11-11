#ifndef PIECE_H_
#define PIECE_H_

#include <list>
#include <vector>
#include "Position.h"
#include "Drawable.h"
#include "Board.h"

class Board;
enum class PieceColor { WHITE, BLACK };

class Piece : public Drawable {
 public:
  Piece(PieceColor color, Position position, Board* board);

  Position getPosition() const;

  PieceColor getColor() const;

  std::list<Position> getPossibleMoves() const;

  float getProbability() const;

  void move(Position position);

  virtual void eat();

  virtual void split(Position position1, Position position2);

  void merge(Position to, Piece* other);

  virtual ~Piece() = default;

 protected:
  Position position_;
  PieceColor color_;
  bool has_moved_;
  Board* board_;
  float probability_;
  std::list<Piece*> splits_;

  virtual std::list<std::pair<int, int>> getVectorBeamMoves_() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves_() const = 0;
  virtual Piece * createSplit_(Position to) = 0;
  virtual void merge_();
  Piece* getPieceFromBoard_(Position &position) const;

 private:
  std::list<Position> getPossibleStepPositions_() const;
  std::list<Position> getPossibleBeamPositions_() const;
  void validateMove_(const Position &position) const;
  void appendToBoard_(Piece* piece);
  bool isSplit_(Piece *other) const;
};

#endif  // PIECE_H_
