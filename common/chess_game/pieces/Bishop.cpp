#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position position) : Piece(color, position) {}

char Bishop::getDrawing() const {
    return 'B';
}

std::list<std::pair<int, int>> Bishop::getVectorBeamMoves() const {
    return {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Bishop::getVectorStepMoves() const {
    return {};
}
