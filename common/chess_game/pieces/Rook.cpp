#include "Rook.h"

Rook::Rook(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char Rook::getDrawing() const {
    return 'R';
}

std::list<std::pair<int, int>> Rook::getVectorBeamMoves_() const {
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
}

std::list<std::pair<int, int>> Rook::getVectorStepMoves_() const {
    return {};
}
void Rook::createSplit_(Position to, float probability) {
    auto* split = new Rook(color_, position_, board_, probability);
    split->move(to);
    appendToBoard_(split);
}
Rook::Rook(PieceColor color, Position position, Board *board, float probability)
    : Piece(color, position, board, probability) {}
