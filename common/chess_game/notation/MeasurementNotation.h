#ifndef QUANTUM_CHESS_COMMON_CHESS_GAME_NOTATION_MEASUREMENTNOTATION_H_
#define QUANTUM_CHESS_COMMON_CHESS_GAME_NOTATION_MEASUREMENTNOTATION_H_

#include "MoveNotation.h"

class MeasurementNotation : public MoveNotation {
 public:
  MeasurementNotation(bool result);

  std::string getString() override;

 private:
  bool result_;
};

#endif  // QUANTUM_CHESS_COMMON_CHESS_GAME_NOTATION_MEASUREMENTNOTATION_H_
