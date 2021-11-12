#include "King.h"

King::King(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char King::getDrawing() const {
    return 'W';
}

std::list<std::pair<int, int>> King::getVectorBeamMoves_() const {
    return {};
}

std::list<std::pair<int, int>> King::getVectorStepMoves_() const {
    // Castle: todo
    return {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

void King::eat() {
//    Piece::eat();  // todo: finish game when effectively eaten
    if (board_ != nullptr) {
        board_->finishGame(
            color_ == PieceColor::WHITE ? PieceColor::BLACK
                                        : PieceColor::WHITE);
    }
}

Piece * King::createSplit_(Position to) {
    return new King(color_, to, board_);
}
