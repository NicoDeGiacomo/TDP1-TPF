#include <stdexcept>
#include <algorithm>
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

    bool confirmed;
    if (getProbability() < 1.0f) {
        confirmed = measure_();
        if (!confirmed) {
            return;
        }
    }

    confirmed = pieceTo->measure_();
    try {
        move_(position);
    } catch (std::invalid_argument &e) {
        // After the measurement, the move might invalid and should not be done.
    }
    if (confirmed) {
        pieceTo->eat();
    }
}

void Piece::move_(Position position, bool merge) {
    validateMove_(position, merge);
    if (!merge) {
        bool entangled = checkEntanglement_(position);
        if (entangled) {
            return;
        }
    }
    position_ = position;
    has_moved_ = true;
}

bool Piece::measure_() {
    if (getProbability() >= 1.0f) {
        return true;
    }

    if (board_->getRandomValue_() <= getProbability()) {
        confirmEntanglement_();
        confirmSplit_();
        return true;
    } else {
        denyEntanglement_();
        denySplit_();
        return false;
    }
}

std::list<Position> Piece::getPossibleMoves(bool merge) const {
    std::list<Position> possibleStepPositions = getPossibleStepPositions_(merge);
    std::list<Position> possibleBeamPositions = getPossibleBeamPositions_(merge);
    if (possibleStepPositions.empty()) {
        return possibleBeamPositions;
    }

    return possibleStepPositions;  // todo join lists
}

std::list<Position> Piece::getPossibleStepPositions_(__attribute__((unused)) bool merge) const {
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

std::list<Position> Piece::getPossibleBeamPositions_(bool merge) const {
    std::list<Position> possiblePositions;
    for (auto move: getVectorBeamMoves_()) {
        int x = position_.getX();
        int y = position_.getY();
        bool entangled = false;
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);
                Piece* otherPiece = getPieceFromBoard_(newPosition);
                if (otherPiece != nullptr) {
                    if (otherPiece->getProbability() >= 1.0f) {
                        if (color_ != otherPiece->color_) {
                            possiblePositions.push_back(newPosition);
                        }
                        break;
                    }

                    if (isSplit_(otherPiece)) {
                        if (merge) {
                            possiblePositions.push_back(newPosition);
                        }
                    } else if (color_ != otherPiece->color_) {
                        possiblePositions.push_back(newPosition);
                    }

                    if (entangled) {
                        break;
                    } else if (getProbability() >= 1.0f && !merge) {
                        entangled = true;
                    }
                } else {
                    possiblePositions.push_back(newPosition);
                }
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

void Piece::validateMove_(const Position &position, bool merge) const {
    std::list<Position> positions = getPossibleMoves(merge);
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

    if (other->position_ != to) {
        other->validateMove_(to, true);
    }
    if (position_ != to) {
        move_(to, true);
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

bool Piece::checkEntanglement_(Position to) {
    if (getProbability() < 1.0f) {
        return false;
    }
    Piece* entanglement;
    bool found = false;
    for (auto move: getVectorBeamMoves_()) {
        entanglement = nullptr;
        int x = position_.getX();
        int y = position_.getY();
        while (true) {
            try {
                x += move.first;
                y += move.second;
                Position newPosition(x, y);

                Piece* otherPiece = getPieceFromBoard_(newPosition);
                if (otherPiece != nullptr && !isSplit_(otherPiece) && otherPiece->getProbability() <= 1.0f) {
                    entanglement = otherPiece;
                    continue;
                }

                if (newPosition == to) {
                    found = true;
                    break;
                }
            } catch (std::invalid_argument &) {
                break;
            }
        }

        if (found) {
            break;
        }
    }

    if (found && entanglement != nullptr) {
        entagle_(entanglement, to);
        return true;
    }

    return false;
}

void Piece::entagle_(__attribute__((unused)) Piece *with, Position to) {
    auto* split1 = createSplit_(position_);
    auto* split2 = createSplit_(to);

    splits_->addSplit(this, split1, split2);

    split2->splits_->addEntanglement(split2, with);
    with->splits_->addEntanglement(with, split2);
}

void Piece::merge_() {}

void Piece::removeFromBoard_() {
    board_->pieces_.remove(this);
}

void Piece::confirmSplit_() {
    splits_->confirmSplit(this);
}

void Piece::confirmEntanglement_() {
    splits_->confirmEntanglement(this);
}

void Piece::denyEntanglement_() {
    splits_->denyEntanglement(this);
}

void Piece::denySplit_() {
    splits_->removeSplit(this);
}

void Piece::resetSplits_() {
    splits_ = std::make_shared<PieceSplits>(this);
}

std::list<Position> Piece::getEntanglements() const {
    return splits_->getEntanglements(this);
}
