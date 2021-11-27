#include "King.h"

#include <utility>

King::King(PieceColor color, Position position, Board* board) : Piece(color, position, board, 'k') {}

King::King(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits) : Piece(color, position, board, std::move(splits), 'k') {}


std::list<std::pair<int, int>> King::getVectorBeamMoves_() const {
    return {};
}

std::list<std::pair<int, int>> King::getVectorStepMoves_() const {
    // todo castling
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
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
