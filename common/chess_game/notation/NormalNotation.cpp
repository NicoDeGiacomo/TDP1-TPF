#include "NormalNotation.h"
#include "NormalMoveMessage.h"

NormalNotation::NormalNotation(Position from, Position to) : from_(from), to_(to) {}

std::string NormalNotation::getString() {
    return "N" + from_.getAlgebraic() + to_.getAlgebraic();
}

std::shared_ptr<Message> NormalNotation::getMoveMessage() {
    return std::make_shared<NormalMoveMessage>(from_, to_);
}

bool NormalNotation::isTurnEndingMove() {
    return true;
}
