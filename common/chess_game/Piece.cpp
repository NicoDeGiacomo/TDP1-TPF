#include <stdexcept>
#include <algorithm>
#include <random>
#include <utility>
#include "Piece.h"

Piece::Piece(PieceColor color, Position position, const char pieceKey)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(nullptr),
      splits_(std::make_shared<PieceSplits>(this)),
      pieceKey_(pieceKey) {}

Piece::Piece(PieceColor color, Position position, Board *board, const char pieceKey)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      splits_(std::make_shared<PieceSplits>(this)),
      pieceKey_(pieceKey) {}

Piece::Piece(PieceColor color, Position position, Board *board, std::shared_ptr<PieceSplits> splits, const char pieceKey)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      splits_(std::move(splits)),
      pieceKey_(pieceKey) {}

Position Piece::getPosition() const {
    return position_;
}

PieceColor Piece::getColor() const {
    return color_;
}

char Piece::getDrawing() const {
    if (color_ == PieceColor::WHITE)
        return toupper(pieceKey_);
    return tolower(pieceKey_);
}

void Piece::move(Position position) {
    validateMove_(position);

    auto pieceTo = board_->getPiece(position);
    if (pieceTo == nullptr) {
        move_(position);
        return;
    }

    pieceTo->measure_();

    pieceTo = board_->getPiece(position);
    try {
        move_(position);
    } catch (std::invalid_argument &e) {
        // After the measurement, the move might invalid and should not be done.
    }

    if (pieceTo != nullptr) {
        pieceTo->eat();
    }
}

void Piece::move_(Position position) {
    validateMove_(position);
    position_ = position;
    has_moved_ = true;
}

void Piece::measure_() {
    if (getProbability() >= 1.0f) {
        return;
    }

    std::uniform_int_distribution<int> distribution(1, 100);
    std::mt19937 engine(board_->seed_);
    int value = distribution(engine);
    if (((float) value)  / 100 <= getProbability()) {
        splits_->confirmSplit(this);
    } else {
        splits_->removeSplit(this);
    }
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
            if (otherPiece == nullptr || otherPiece->color_ != color_ || isSplit_(otherPiece)) {
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
                    if (isSplit_(otherPiece)) {
                        possiblePositions.push_back(newPosition);
                        continue;
                    }
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
    std::list<Position> positions = getPossibleMoves();
    bool found = std::find(positions.begin(), positions.end(), position) != positions.end();
    if (!found) {
        throw std::invalid_argument("Invalid move: not possible.");
    }
}

void Piece::eat() {
    removeFromBoard_();
    delete this;
}

void Piece::split(Position position1, Position position2) {
    validateMove_(position1);
    validateMove_(position2);

    auto* split1 = createSplit_(position1);
    auto* split2 = createSplit_(position2);
    splits_->addSplit(this, split1, split2);
}

void Piece::merge(Position to, Piece* other) {
    merge_();
    other->merge_();

    if (!isSplit_(other)) {
        throw std::invalid_argument("Invalid move: non split.");
    }

    if (position_ != to) {
        move_(to);
    }
    splits_->mergeSplits(this, other);
}

void Piece::appendToBoard_() {
    board_->pieces_.push_back(this);
}

float Piece::getProbability() const {
    return splits_->getProbability(this);
}

bool Piece::isSplit_(Piece *other) const {
    return splits_->contains(this) && splits_->contains(other);
}

void Piece::merge_() {}

void Piece::removeFromBoard_() {
    board_->pieces_.remove(this);
}

void Piece::resetSplits() {
    splits_ = std::make_shared<PieceSplits>(this);
}
