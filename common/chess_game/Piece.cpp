#include "Piece.h"

Piece::Piece(PieceColor color, Position position)
    : color_(color), position_(position) {}

Position Piece::getPosition() const {
    return position_;
}
void Piece::move(Position position) {
    position_ = position;
}

std::list<Position> Piece::getPossibleMoves() const {
    return {};
}
