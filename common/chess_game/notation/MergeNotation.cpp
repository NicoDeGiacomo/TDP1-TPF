#include "MergeNotation.h"

MergeNotation::MergeNotation(Position from1, Position from2, Position to)
    : from1_(from1),
      from2_(from2),
      to_(to) {}

std::string MergeNotation::getString() {
    return "M" + from1_.getAlgebraic() + from2_.getAlgebraic() + to_.getAlgebraic();
}
