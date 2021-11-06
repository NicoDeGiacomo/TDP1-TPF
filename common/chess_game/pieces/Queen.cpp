#include "Queen.h"

Queen::Queen(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char Queen::getDrawing() const {
    return 'Q';
}

std::list<std::pair<int, int>> Queen::getVectorBeamMoves_() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Queen::getVectorStepMoves_() const {
    return {};
}

Piece * Queen::createSplit_(Position to) {
    return new Queen(color_, to, board_);
}
