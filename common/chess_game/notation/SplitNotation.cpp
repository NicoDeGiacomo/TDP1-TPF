#include "SplitNotation.h"

SplitNotation::SplitNotation(Position from, Position to1, Position to2) : from_(from), to1_(to1), to2_(to2) {}

std::string SplitNotation::getString() {
    return "S" + from_.getAlgebraic() + to1_.getAlgebraic() + to2_.getAlgebraic();
}
