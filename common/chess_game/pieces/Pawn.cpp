#include "Pawn.h"

#include <stdexcept>

Pawn::Pawn(PieceColor color, Position position, Board* board) : Piece(color, position, board, 'p') {}


std::list<std::pair<int, int>> Pawn::getVectorBeamMoves_() const {
    return {};
}

std::list<std::pair<int, int>> Pawn::getVectorStepMoves_() const {
    int direction = color_ == PieceColor::WHITE ? 1 : -1;
    std::list<std::pair<int, int>> moves {};

    // Cannot capture forward
    try {
        Position front
            (position_.getX(), position_.getY() + (1 * direction));
        Piece* frontPiece = getPieceFromBoard_(front);
        if (frontPiece == nullptr) {
            moves.emplace_back(0, 1 * direction);
        }
    } catch (std::invalid_argument &e) {}

    // Different optional first move
    if (!has_moved_) {
        try {
            Position front2
                (position_.getX(), position_.getY() + (2 * direction));
            Piece* front2Piece = getPieceFromBoard_(front2);
            if (front2Piece == nullptr) {
                moves.emplace_back(0, 2 * direction);
            }
        } catch (std::invalid_argument &e) {}
    }

    // Different move when taking a piece
    try {
        Position rightDiagonal
            (position_.getX() + 1, position_.getY() + (1 * direction));
        Piece *otherPiece = getPieceFromBoard_(rightDiagonal);
        if (otherPiece != nullptr) {
            moves.emplace_back(1, 1 * direction);
        }
    } catch (std::invalid_argument &e) {}

    try {
        Position leftDiagonal
            (position_.getX() - 1, position_.getY() + (1 * direction));
        Piece *otherPiece2 = getPieceFromBoard_(leftDiagonal);
        if (otherPiece2 != nullptr) {
            moves.emplace_back(-1, 1 * direction);
        }
    } catch (std::invalid_argument &e) {}

    // todo: en passant

    return moves;
}
Piece * Pawn::createSplit_(__attribute__((unused)) Position to) {
    throw std::invalid_argument("Invalid move: cannot split a pawn.");
}

void Pawn::merge_() {
    throw std::invalid_argument("Invalid move: cannot merge a pawn.");
}

bool Pawn::checkEntanglement_(__attribute__((unused)) Position to) {
    return false;
}
