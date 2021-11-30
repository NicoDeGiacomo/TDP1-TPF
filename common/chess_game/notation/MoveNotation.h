#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_

#include "Position.h"

class MoveNotation {
 public:
  virtual std::string getString() = 0;
  virtual ~MoveNotation() = default;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_
