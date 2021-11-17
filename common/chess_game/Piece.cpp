#include <stdexcept>
#include <algorithm>
#include <random>
#include "Piece.h"

Piece::Piece(PieceColor color, Position position)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(nullptr),
      probability_(1.0),
      splits2_(new PieceSplits(this)) {}

Piece::Piece(PieceColor color, Position position, Board *board)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      probability_(1.0),
      splits2_(new PieceSplits(this)) {}

Piece::Piece(PieceColor color, Position position, Board *board, PieceSplits* splits)
    : position_(position),
      color_(color),
      has_moved_(false),
      board_(board),
      probability_(1.0),
      splits2_(splits) {}

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
    // todo
    if (this->probability_ < 1.0f) {
        // performMeasurement();
        std::vector<std::pair<int, Piece*>> probabilities;
        for (auto piece : splits_) {
            probabilities.emplace_back((int) piece->probability_ * 100, piece);
        }



        std::random_device rd;
        std::uniform_int_distribution<int> distribution(1, 100);
        std::mt19937 engine(rd());
        int value = distribution(engine);

        int sum = 0;
        for (auto probability : probabilities) {
            sum += probability.first;
            if (sum > value) {
                // pieza que queda viva
                auto piece = probability.second;
                for (auto split : piece->splits_) {
                    removeFromBoardAndDelete_(split);
                }
                piece->probability_ = 1.0f;
            }
        }
    } else {
        removeFromBoardAndDelete_(this);
    }
}

void Piece::split(Position position1, Position position2) {
    validateMove_(position1);
    validateMove_(position2);

//    auto* split = createSplit_(position2);
//    appendToBoard_(split);
//    split->splits_.push_back(this);
//    split->splits_.insert(split->splits_.begin(), splits_.begin(), splits_.end());
//    split->probability_ = probability_ / 2;
//
//    move(position1);
//    for (auto* piece : splits_) {
//        piece->splits_.push_back(split);
//    }
//    splits_.push_back(split);
//    probability_ = probability_ / 2;
    auto* split1 = createSplit_(position1);
    auto* split2 = createSplit_(position2);
    splits2_->addSplit(this, split1, split2);
}

void Piece::merge(Position to, Piece* other) {
    merge_();
    other->merge_();

    if (!isSplit_(other)) {
        throw std::invalid_argument("Invalid move: non split.");
    }

    // todo: Move must be valid. Not exception safe strong.
    splits2_->mergeSplits(this, other);
    if (position_ != to) {
        move(to);
    }
}

void Piece::appendToBoard_(Piece* piece) {
    board_->pieces_.push_back(piece);
}

float Piece::getProbability() const {
    return probability_;
}

bool Piece::isSplit_(Piece *other) const {
    return splits2_->contains(this) && splits2_->contains(other);
}

void Piece::merge_() {}

void Piece::removeFromBoardAndDelete_(Piece *piece) {
    removeFromBoard_(piece);
    delete piece;
}

void Piece::removeFromBoard_(Piece *piece) {
    board_->pieces_.remove(piece);
}

void Piece::finishMeasure_() {
    delete splits2_;
    splits2_ = new PieceSplits(this);
}

Piece::~Piece() {
    // todo
    if (splits2_ != nullptr) {
        delete splits2_;
    }
}
