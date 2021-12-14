#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_NORMALMOVENOTATION_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_NORMALMOVENOTATION_H_

#include "MoveNotation.h"

class NormalNotation : public MoveNotation {
 public:
  NormalNotation(Position from, Position to);
  std::string getString() override;
  std::shared_ptr<Message> getMoveMessage() override;
  bool isTurnEndingMove() override;
 private:
  Position from_;
  Position to_;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_MOVES_NORMALMOVENOTATION_H_
