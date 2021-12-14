#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_

#include "Position.h"
#include "Message.h"

class Message;

class MoveNotation {
 public:
  virtual ~MoveNotation() = default;
  virtual std::string getString() = 0;
  virtual std::shared_ptr<Message> getMoveMessage() = 0;
  virtual bool isTurnEndingMove() = 0;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_MOVE_H_
