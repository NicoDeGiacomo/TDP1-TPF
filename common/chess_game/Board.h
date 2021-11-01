#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include "Piece.h"

class Piece;
enum class PieceColor;

class Board {
 public:
  Board();

  std::list<Piece*>::const_iterator begin() const;

  std::list<Piece*>::const_iterator end() const;

  Piece *getPiece(Position position) const;

  std::list<Position> getPossibleMoves(Position position) const;

  bool isFinished() const;

  void move(Position from, Position to);

  void finishGame(PieceColor winner);

  virtual ~Board();

 private:
  std::list<Piece*> pieces_;
  PieceColor turn_;
  bool finished_;

  void generatePiecesForColor(PieceColor color);
};

#endif  // BOARD_H_
