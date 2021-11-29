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

  std::list<Position> getPossibleMoves(bool merge = false) const;

  std::list<Position> getEntanglements() const;

  float getProbability() const;

  Position getPosition() const;

  PieceColor getColor() const;

  char getDrawing() const override;

  virtual ~Piece() = default;

 protected:
  Position position_;
  PieceColor color_;
  bool has_moved_;
  Board* board_;
  std::shared_ptr<PieceSplits> splits_;
    const char pieceKey_;

  Piece(PieceColor color, Position position, const char pieceKey);
  Piece(PieceColor color, Position position, Board* board, const char pieceKey);
  Piece(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits, const char pieceKey);
  virtual std::list<std::pair<int, int>> getVectorBeamMoves_() const = 0;
  virtual std::list<std::pair<int, int>> getVectorStepMoves_() const = 0;
  virtual Piece * createSplit_(Position to) = 0;
  virtual void merge_();
  Piece* getPieceFromBoard_(Position &position) const;

 private:
  void move_(Position position, bool merge = false);
  bool measure_();
  std::list<Position> getPossibleStepPositions_(__attribute__((unused)) bool merge = false) const;
  std::list<Position> getPossibleBeamPositions_(bool merge = false) const;
  void validateMove_(const Position &position, bool merge = false) const;
  void appendToBoard_();
  bool isSplit_(Piece *other) const;
  virtual bool checkEntanglement_(Position to);
  void entagle_(__attribute__((unused)) Piece *with, Position to);
  void confirmSplit_();
  void confirmEntanglement_();
  void denyEntanglement_();
  void denySplit_();
  void resetSplits_();
  void removeFromBoard_();

  friend PieceSplits;
};

#endif  // PIECE_H_
