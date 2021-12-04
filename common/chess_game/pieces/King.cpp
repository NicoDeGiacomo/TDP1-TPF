#include "King.h"

#include <utility>

King::King(PieceColor color, Position position, Board* board) : Piece(color, position, board, 'k') {}

King::King(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits) : Piece(color, position, board, std::move(splits), 'k') {}


std::list<std::pair<int, int>> King::getVectorBeamMoves_() const {
    return {};
}

std::list<std::pair<int, int>> King::getVectorStepMoves_() const {
    std::list<std::pair<int, int>> moves {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    if (!has_moved_) {
        auto position1 = Position(1, position_.getY());
        auto position2 = Position(8, position_.getY());
        auto rook1 = getPieceFromBoard_(position1);
        auto rook2 = getPieceFromBoard_(position2);

        if (rook1 != nullptr && !rook1->has_moved_) {
            auto empty1 = Position(2, position_.getY());
            auto empty2 = Position(3, position_.getY());
            auto empty3 = Position(4, position_.getY());
            if (!getPieceFromBoard_(empty1) && !getPieceFromBoard_(empty2)
                && !getPieceFromBoard_(empty3)) {
                moves.emplace_back(-2, 0);
            }
        }

        if (rook2 != nullptr && !rook2->has_moved_) {
            auto empty1 = Position(6, position_.getY());
            auto empty2 = Position(7, position_.getY());
            if (!getPieceFromBoard_(empty1) && !getPieceFromBoard_(empty2)) {
                moves.emplace_back(2, 0);
            }
        }
    }

    return moves;
}

void King::eat() {
    if (board_ != nullptr) {
        board_->finishGame(
            color_ == PieceColor::WHITE ? PieceColor::BLACK
                                        : PieceColor::WHITE);
    }
    Piece::eat();
}

Piece * King::createSplit_(Position to) {
    return new King(color_, to, board_, splits_);
}

void King::move_(Position position, bool merge) {
    validateMove_(position, merge);
    if (!has_moved_ && !merge) {
        auto deltaX = position_.getX() - position.getX();

        Piece::move_(position, merge);

        if (deltaX == 2) {
            auto rookPos = Position(1, position_.getY());
            auto rook = getPieceFromBoard_(rookPos);
            if (rook != nullptr) {
                rook->position_ = Position(position.getX() + 1, position_.getY());
                rook->has_moved_ = true;
            }
        }

        if (deltaX == -2) {
            auto rookPos = Position(8, position_.getY());
            auto rook = getPieceFromBoard_(rookPos);
            if (rook != nullptr) {
                rook->position_ = Position(position.getX() - 1, position_.getY());
                rook->has_moved_ = true;
            }
        }
    } else {
        Piece::move_(position, merge);
    }
}
