#include "Queen.h"

Queen::Queen(PieceColor color, Position position) : Piece(color, position) {}

char Queen::getDrawing() const {
    return 'Q';
}

std::list<std::pair<int, int>> Queen::getVectorBeamMoves() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Queen::getVectorStepMoves() const {
    return {};
}
