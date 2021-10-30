#include "Knight.h"

Knight::Knight(PieceColor color, Position position) : Piece(color, position) {}

char Knight::getDrawing() const {
    return 'K';
}

std::list<std::pair<int, int>> Knight::getPossibleBeamMoves() const {
    return {};
}

std::list<std::pair<int, int>> Knight::getPossibleStepMoves() const {
    return {};
}
