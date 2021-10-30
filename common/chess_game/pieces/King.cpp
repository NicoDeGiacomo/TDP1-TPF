#include "King.h"

King::King(PieceColor color, Position position) : Piece(color, position) {}

char King::getDrawing() const {
    return 'W';
}
std::list<std::pair<int, int>> King::getPossibleBeamMoves() const {
    return {};
}
std::list<std::pair<int, int>> King::getPossibleStepMoves() const {
    return {};
}


