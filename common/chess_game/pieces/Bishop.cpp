#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char Bishop::getDrawing() const {
    return 'B';
}

std::list<std::pair<int, int>> Bishop::getVectorBeamMoves_() const {
    return {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Bishop::getVectorStepMoves_() const {
    return {};
}

Piece * Bishop::createSplit_(Position to) {
    return new Bishop(color_, to, board_);
}
