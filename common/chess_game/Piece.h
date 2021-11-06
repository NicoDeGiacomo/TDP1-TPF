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

  virtual ~Piece() = default;

 protected:
  Position position_;
  PieceColor color_;
  bool has_moved_;
  Board* board_;
  float probability_;
  std::vector<Piece*> splits_;

  Piece(PieceColor color, Position position, Board* board, float probability);
  virtual Piece * createSplit_(Position to) = 0;
  virtual std::list<std::pair<int, int>> getVectorBeamMoves_() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves_() const = 0;
  Piece* getPieceFromBoard_(Position &position) const;
  void appendToBoard_(Piece* piece);

 private:
  std::list<Position> getPossibleStepPositions_() const;
  std::list<Position> getPossibleBeamPositions_() const;
  void validateMove_(const Position &position) const;
};

#endif  // PIECE_H_
