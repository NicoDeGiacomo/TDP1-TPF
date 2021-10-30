#include "Piece.h"

Piece::Piece(PieceColor color, Position position)
    : has_moved_(false), color_(color), position_(position) {}

Position Piece::getPosition() const {
    return position_;
}
void Piece::move(Position position) {
    // todo validate with possible moves
    position_ = position;
    has_moved_ = true;
}

std::list<Position> Piece::getPossiblePositions() const {
    std::list<Position> possiblePositions;
    for (auto move: getPossibleStepMoves()) {
        Position newPosition
            (position_.getX() + move.first, position_.getY() + move.second);
        possiblePositions.push_back(newPosition);
    }

    return possiblePositions;
}
