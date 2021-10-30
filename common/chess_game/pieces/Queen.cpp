#include "Queen.h"

Queen::Queen(PieceColor color, Position position) : Piece(color, position) {}

char Queen::getDrawing() const {
    return 'Q';
}
std::list<std::pair<int, int>> Queen::getPossibleBeamMoves() const {
    return {};
}
std::list<std::pair<int, int>> Queen::getPossibleStepMoves() const {
    return {};
}
