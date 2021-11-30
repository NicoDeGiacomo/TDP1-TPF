#include "NormalNotation.h"

NormalNotation::NormalNotation(Position from, Position to) : from_(from), to_(to) {}

std::string NormalNotation::getString() {
    return "N" + from_.getAlgebraic() + to_.getAlgebraic();
}
