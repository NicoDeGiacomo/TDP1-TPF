#include "Rook.h"

Rook::Rook(PieceColor color, Position position) : Piece(color, position) {}

char Rook::getDrawing() const {
    return 'R';
}

std::list<std::pair<int, int>> Rook::getVectorBeamMoves() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
}

std::list<std::pair<int, int>> Rook::getVectorStepMoves() const {
    return {};
}
