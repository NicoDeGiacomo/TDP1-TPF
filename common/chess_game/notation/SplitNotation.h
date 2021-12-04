#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_SPLITMOVENOTATION_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_SPLITMOVENOTATION_H_

#include "MoveNotation.h"

class SplitNotation : public MoveNotation {
 public:
  SplitNotation(Position from, Position to1, Position to2);
  std::string getString() override;
  std::shared_ptr<Message> getMoveMessage() override;

 private:
  Position from_;
  Position to1_;
  Position to2_;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_SPLITMOVENOTATION_H_
