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

Knight::Knight(PieceColor color,
               Position position,
               Board *board,
               float probability) : Piece(color, position, board, probability) {}

void Knight::createSplit_(Position to, float probability) {
    auto* split = new Knight(color_, position_, board_, probability);
    split->move(to);
    appendToBoard_(split);
}
