#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include "Piece.h"

class Board {
  std::list<Piece> pieces_;

  void generatePiecesForColor(PieceColor color);

 public:
  Board();

  std::list<Piece>::iterator begin();

  std::list<Piece>::iterator end();
};

#endif  // BOARD_H_
