#ifndef BOARD_H_
#define BOARD_H_

#include <list>
#include "Piece.h"

class Board {
  std::list<Piece*> pieces_;

 public:
  Board();
};

#endif  // BOARD_H_
