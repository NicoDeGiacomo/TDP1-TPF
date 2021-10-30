#include "Pawn.h"

Pawn::Pawn(PieceColor color, Position position) : Piece(color, position) {}

char Pawn::getDrawing() const {
    return 'p';
}

std::list<std::pair<int, int>> Pawn::getPossibleBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Pawn::getPossibleStepMoves() const {
    // todo: depende del color
    if (!has_moved_) {
        return {{0, 1}, {0, 2}};
    }
    return {{0, 1}};
}
