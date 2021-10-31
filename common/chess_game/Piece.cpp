#include <stdexcept>
#include <algorithm>
#include "Piece.h"

Piece::Piece(PieceColor color, Position position)
    : color_(color), has_moved_(false), position_(position) {}

Position Piece::getPosition() const {
    return position_;
}

void Piece::move(Position position) {
    std::list<Position> positions = getPossiblePositions();
    bool found = std::find(positions.begin(), positions.end(), Position(1, 2)) != positions.end();
    if (!found) {
        throw std::invalid_argument("Invalid move.");
    }

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
    for (auto move: getVectorStepMoves()) {
        try {
            Position newPosition
                (position_.getX() + move.first, position_.getY() + move.second);
            possiblePositions.push_back(newPosition);
        } catch (std::invalid_argument &) {
            continue;
        }
    }

    return possiblePositions;
}

std::list<Position> Piece::getPossibleBeamPositions() const {
    std::list<Position> possiblePositions;
    for (auto move: getVectorBeamMoves()) {
        int x = position_.getX();
        int y = position_.getY();
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);
                possiblePositions.push_back(newPosition);
            } catch (std::invalid_argument &) {
                break;
            }
        }
    }

    return possiblePositions;
}
