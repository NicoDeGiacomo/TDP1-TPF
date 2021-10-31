#include "Pawn.h"

Pawn::Pawn(PieceColor color, Position position) : Piece(color, position) {}

char Pawn::getDrawing() const {
    return 'p';
}

std::list<std::pair<int, int>> Pawn::getPossibleBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Pawn::getPossibleStepMoves() const {
    int move = color_ == WHITE ? 1 : -1;
    // todo: depende del color
    if (!has_moved_) {
        return {{0, 1 * move}, {0, 2 * move}};
    }
    return {{0, 1 * move}};
}
