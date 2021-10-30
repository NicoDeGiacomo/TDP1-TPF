#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include "Piece.h"

class Board {
 public:
  Board();

  std::list<Piece>::iterator begin();

  std::list<Piece>::iterator end();

 private:
  std::list<Piece> pieces_;

  void generatePiecesForColor(PieceColor color);
};

#endif  // BOARD_H_
