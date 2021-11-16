#include "Knight.h"

Knight::Knight(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

Knight::Knight(PieceColor color, Position position, Board* board, PieceSplits* splits) : Piece(color, position, board, splits) {}

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
    return new Knight(color_, to, board_, splits2_);
}
