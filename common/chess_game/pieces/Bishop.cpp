#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position position) : Piece(color, position) {}

char Bishop::getDrawing() const {
    return 'B';
}

std::list<std::pair<int, int>> Bishop::getPossibleBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Bishop::getPossibleStepMoves() const {
    return {};
}
