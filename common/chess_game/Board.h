#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include <random>
#include "Piece.h"

class Piece;
enum class PieceColor;

class Board {
 public:
  Board(bool empty = false, unsigned int seed = 0);

  std::list<Piece*>::const_iterator begin() const;

  std::list<Piece*>::const_iterator end() const;

  PieceColor getCurrentTurn();

  void move(Position from, Position to);

  void split(Position from, Position to1, Position to2);

  void merge(Position from1, Position from2, Position to);

  void finishGame(__attribute__((unused)) PieceColor winner);

  Piece* getPiece(Position position) const;

  std::list<Position> getPossibleMoves(Position position) const;

  bool isFinished() const;

  virtual ~Board();

    void printBoard();

private:
  std::list<Piece*> pieces_;
  PieceColor turn_;
  bool finished_;
  std::uniform_int_distribution<int> distribution_;
  std::mt19937 engine_;

  float getRandomValue_();
  Piece* getPieceWithValidations_(Position position);
  static void validatePieceNotNull_(Piece* piece);
  void validateTurn_(Piece* piece);
  void changeTurn_();
  void generatePiecesForColor_(PieceColor color);

  friend Piece;
};

#endif  // BOARD_H_
