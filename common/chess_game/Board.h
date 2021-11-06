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

  std::list<Position> getPossibleMoves(Position position) const;

  Piece* getPiece(Position position) const;

  bool isFinished() const;

  void move(Position from, Position to);

  void split(Position from, Position to1, Position to2);

  void merge(Position pos1, Position pos2);

  void finishGame(__attribute__((unused)) PieceColor winner);

  virtual ~Board();

 private:
  std::list<Piece*> pieces_;
  PieceColor turn_;
  bool finished_;

  void generatePiecesForColor_(PieceColor color);

  friend Piece;
  void changeTurn();
};

#endif  // BOARD_H_
