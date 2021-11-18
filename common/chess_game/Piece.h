#ifndef PIECE_H_
#define PIECE_H_

#include <list>
#include <vector>
#include <memory>
#include "Position.h"
#include "Drawable.h"
#include "Board.h"
#include "PieceSplits.h"

class Board;
class PieceSplits;
enum class PieceColor { WHITE, BLACK };

class Piece : public Drawable {
 public:
  void move(Position position);

  virtual void split(Position position1, Position position2);

  void merge(Position to, Piece* other);

  virtual void eat();

  std::list<Position> getPossibleMoves() const;

  float getProbability() const;

  Position getPosition() const;

  PieceColor getColor() const;

  virtual ~Piece() = default;

 protected:
  Position position_;
  PieceColor color_;
  bool has_moved_;
  Board* board_;
  std::shared_ptr<PieceSplits> splits_;

  Piece(PieceColor color, Position position);
  Piece(PieceColor color, Position position, Board* board);
  Piece(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits);
  virtual std::list<std::pair<int, int>> getVectorBeamMoves_() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves_() const = 0;
  virtual Piece * createSplit_(Position to) = 0;
  virtual void merge_();
  Piece* getPieceFromBoard_(Position &position) const;

 private:
  std::list<Position> getPossibleStepPositions_() const;
  std::list<Position> getPossibleBeamPositions_() const;
  void validateMove_(const Position &position) const;
  void appendToBoard_();
  bool isSplit_(Piece *other) const;
  void finishMeasure_();
  void removeFromBoard_();

  friend PieceSplits;
};

#endif  // PIECE_H_
