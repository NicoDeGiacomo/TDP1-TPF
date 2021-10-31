#include "Pawn.h"

Pawn::Pawn(PieceColor color, Position position) : Piece(color, position) {}

char Pawn::getDrawing() const {
    return 'p';
}

std::list<std::pair<int, int>> Pawn::getVectorBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Pawn::getVectorStepMoves() const {
    int move = color_ == WHITE ? 1 : -1;
    if (!has_moved_) {
        return {{0, 1 * move}, {0, 2 * move}};
    }
    return {{0, 1 * move}};
}
