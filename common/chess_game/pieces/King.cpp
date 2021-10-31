#include "King.h"

King::King(PieceColor color, Position position) : Piece(color, position) {}

char King::getDrawing() const {
    return 'W';
}

std::list<std::pair<int, int>> King::getVectorBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> King::getVectorStepMoves() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}
