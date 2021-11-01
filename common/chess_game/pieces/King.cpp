#include "King.h"

King::King(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char King::getDrawing() const {
    return 'W';
}

std::list<std::pair<int, int>> King::getVectorBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> King::getVectorStepMoves() const {
    // Castle: todo
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}
