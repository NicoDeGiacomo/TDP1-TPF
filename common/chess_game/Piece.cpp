#include <stdexcept>
#include <algorithm>
#include "Piece.h"

Piece::Piece(PieceColor color, Position position, Board* board)
    : color_(color), has_moved_(false), position_(position), board_(board) {}

Position Piece::getPosition() const {
    return position_;
}

PieceColor Piece::getColor() const {
    return color_;
}

void Piece::move(Position position) {
    std::list<Position> positions = getPossibleMoves();
    bool found = std::find(positions.begin(), positions.end(), position) != positions.end();
    if (!found) {
        throw std::invalid_argument("Invalid move: not possible.");
    }

    position_ = position;
    has_moved_ = true;
}

std::list<Position> Piece::getPossibleMoves() const {
    std::list<Position> possibleStepPositions = getPossibleStepPositions_();
    std::list<Position> possibleBeamPositions = getPossibleBeamPositions_();
    if (possibleStepPositions.empty()) {
        return possibleBeamPositions;
    }
    return possibleStepPositions;  // todo join lists

}

std::list<Position> Piece::getPossibleStepPositions_() const {
    std::list<Position> possiblePositions;
    for (auto move: getVectorStepMoves()) {
        try {
            Position newPosition
                (position_.getX() + move.first, position_.getY() + move.second);
            Piece* otherPiece = getPieceFromBoard(newPosition);
            if (otherPiece == nullptr || otherPiece->color_ != color_) {
                possiblePositions.push_back(newPosition);
            }
        } catch (std::invalid_argument &) {
            continue;
        }
    }

    return possiblePositions;
}

std::list<Position> Piece::getPossibleBeamPositions_() const {
    std::list<Position> possiblePositions;
    for (auto move: getVectorBeamMoves()) {
        int x = position_.getX();
        int y = position_.getY();
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);
                Piece* otherPiece = getPieceFromBoard(newPosition);
                if (otherPiece != nullptr) {
                    if (color_ != otherPiece->color_) {
                        possiblePositions.push_back(newPosition);
                    }
                    break;
                }

                possiblePositions.push_back(newPosition);
            } catch (std::invalid_argument &) {
                break;
            }
        }
    }

    return possiblePositions;
}

Piece *Piece::getPieceFromBoard(Position &position) const {
    return board_ != nullptr ? board_->getPiece(position) : nullptr;
}

void Piece::eat() {}
