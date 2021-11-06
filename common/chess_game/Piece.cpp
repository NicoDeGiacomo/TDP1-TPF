#include <stdexcept>
#include <algorithm>
#include "Piece.h"

Piece::Piece(PieceColor color, Position position, Board *board)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      probability_(1.0) {}

Position Piece::getPosition() const {
    return position_;
}

PieceColor Piece::getColor() const {
    return color_;
}

void Piece::move(Position position) {
    validateMove_(position);
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
    for (auto move: getVectorStepMoves_()) {
        try {
            Position newPosition
                (position_.getX() + move.first, position_.getY() + move.second);
            Piece* otherPiece = getPieceFromBoard_(newPosition);
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
    for (auto move: getVectorBeamMoves_()) {
        int x = position_.getX();
        int y = position_.getY();
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);
                Piece* otherPiece = getPieceFromBoard_(newPosition);
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

Piece *Piece::getPieceFromBoard_(Position &position) const {
    return board_ != nullptr ? board_->getPiece(position) : nullptr;
}

void Piece::validateMove_(const Position &position) const {
    std::__cxx11::list<Position> positions = getPossibleMoves();
    bool found = std::find(positions.begin(), positions.end(), position) != positions.end();
    if (!found) {
        throw std::invalid_argument("Invalid move: not possible.");
    }
}

void Piece::eat() {}

void Piece::split(Position position1, Position position2) {
    validateMove_(position1);
    validateMove_(position2);

    auto* split = createSplit_(position2);
    appendToBoard_(split);
    split->splits_.push_back(this);
    split->probability_ = probability_ / 2;

    move(position1);
    splits_.push_back(split);
    probability_ = probability_ / 2;
}

Piece::Piece(PieceColor color,
             Position position,
             Board *board,
             float probability)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      probability_(probability) {}

void Piece::appendToBoard_(Piece* piece) {
    if (board_ != nullptr) {
        board_->pieces_.push_back(piece);
    }
}

float Piece::getProbability() const {
    return probability_;
}
