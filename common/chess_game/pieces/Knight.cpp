#include "Knight.h"

Knight::Knight(PieceColor color, Position position) : Piece(color, position) {}

char Knight::getDrawing() const {
    return 'K';
}

std::list<std::pair<int, int>> Knight::getVectorBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Knight::getVectorStepMoves() const {
    return {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-2, -1}};
}
