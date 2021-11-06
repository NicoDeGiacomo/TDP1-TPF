#include "Knight.h"

Knight::Knight(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char Knight::getDrawing() const {
    return 'K';
}

std::list<std::pair<int, int>> Knight::getVectorBeamMoves_() const {
    return {};
}

std::list<std::pair<int, int>> Knight::getVectorStepMoves_() const {
    return {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
}

Piece * Knight::createSplit_(Position to) {
    return new Knight(color_, to, board_);
}
