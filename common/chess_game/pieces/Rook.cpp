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

Piece * Rook::createSplit_(Position to) {
    return new Rook(color_, to, board_);
}
