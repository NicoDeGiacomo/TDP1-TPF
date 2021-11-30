#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_MERGEMOVENOTATION_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_MERGEMOVENOTATION_H_

#include "MoveNotation.h"

class MergeNotation : public MoveNotation {
 public:
  MergeNotation(Position from1, Position from2, Position to);

  std::string getString() override;

 private:
  Position from1_;
  Position from2_;
  Position to_;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_MERGEMOVENOTATION_H_
