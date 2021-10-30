#include <stdexcept>
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
    std::list<Position> possibleStepPositions = getPossibleStepPositions();
    std::list<Position> possibleBeamPositions = getPossibleBeamPositions();
    if (possibleStepPositions.empty()) {
        return possibleBeamPositions;
    }
    return possibleStepPositions;  // todo join lists

}

std::list<Position> Piece::getPossibleStepPositions() const {
    std::list<Position> possiblePositions;
    for (auto move: getPossibleStepMoves()) {
        Position newPosition
            (position_.getX() + move.first, position_.getY() + move.second);
        possiblePositions.push_back(newPosition);
    }

    return possiblePositions;
}

std::list<Position> Piece::getPossibleBeamPositions() const {
    std::list<Position> possiblePositions;
    for (auto move: getPossibleBeamMoves()) {
        int x = position_.getX();
        int y = position_.getY();
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);
                possiblePositions.push_back(newPosition);
            } catch (std::invalid_argument&) {
                break;
            }
        }
    }

    return possiblePositions;
}
