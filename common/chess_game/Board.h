#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include <random>
#include "Piece.h"
#include "MoveNotation.h"

#define DUMP_FOLDER_ "/Documents/QuantumChess/"
#define DUMP_FILENAME_ "chess-game"
#define DUMP_SUFFIX_ ".txt"

class Piece;
class MoveNotation;
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

  unsigned int getSeed() const;

  void setSeed(unsigned int seed);

  std::vector<std::shared_ptr<MoveNotation>> getCurrentMoves();

  void generateDump();

  virtual ~Board();

    void printBoard();

private:
  std::list<Piece*> pieces_;
  PieceColor turn_;
  bool finished_;
  std::vector<std::shared_ptr<MoveNotation>> moves_;
  unsigned int seed_;
  std::uniform_int_distribution<int> distribution_;
  std::mt19937 engine_;

  float getRandomValue_();
  Piece* getPieceWithValidations_(Position position);
  static void validatePieceNotNull_(Piece* piece);
  void validateTurn_(Piece* piece);
  void changeTurn_();
  void generatePiecesForColor_(PieceColor color);
  static std::string getDumpPath_(const std::string& folder, int i);

  friend Piece;
};

#endif  // BOARD_H_
