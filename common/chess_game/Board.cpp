#include "Board.h"

#include <Pawn.h>
#include <Rook.h>
#include <Knight.h>
#include <Bishop.h>
#include <Queen.h>
#include <King.h>
#include <algorithm>
#include <stdexcept>
#include <random>

Board::Board(bool empty, unsigned int seed) : turn_(PieceColor::WHITE), finished_(false), seed_(seed) {
    if (!empty) {
        generatePiecesForColor_(PieceColor::WHITE);
        generatePiecesForColor_(PieceColor::BLACK);
    }

    if (seed_ == 0) {
        std::random_device rd;
        seed_ = rd();
    }
}

std::list<Piece*>::const_iterator Board::begin() const {
    return pieces_.begin();
}

std::list<Piece*>::const_iterator Board::end() const {
    return pieces_.end();
}

void Board::move(Position from, Position to) {
    auto pieceFrom = getPiece(from);
    if (pieceFrom == nullptr) {
        throw std::invalid_argument("Invalid move: empty square.");
    }
    if (pieceFrom->getColor() != turn_) {
        throw std::invalid_argument("Invalid move: out of turn.");
    }

    pieceFrom->move(to);
    changeTurn_();
    //for debugging
    printBoard();
}

void Board::split(Position from, Position to1, Position to2) {
    if (to1 == to2) {
        throw std::invalid_argument("Invalid move: equal split positions.");
    }

    auto pieceFrom = getPiece(from);
    auto pieceTo1 = getPiece(to1);
    auto pieceTo2 = getPiece(to2);
    if (pieceTo1 != nullptr || pieceTo2 != nullptr) {
        throw std::invalid_argument("Invalid move: non-empty square.");
    }
    if (pieceFrom == nullptr) {
        throw std::invalid_argument("Invalid move: empty square.");
    }
    if (pieceFrom->getColor() != turn_) {
        throw std::invalid_argument("Invalid move: out of turn.");
    }

    pieceFrom->split(to1, to2);
    changeTurn_();
    //for debugging
    printBoard();
}

void Board::merge(Position from1, Position from2, Position to) {
    if (from1 == from2) {
        throw std::invalid_argument("Invalid move: merging same position.");
    }

    auto* pieceFrom1 = getPiece(from1);
    auto* pieceFrom2 = getPiece(from2);
    if (pieceFrom1 == nullptr || pieceFrom2 == nullptr) {
        throw std::invalid_argument("Invalid move: empty square.");
    }
    if (pieceFrom1->getColor() != turn_ || pieceFrom2->getColor() != turn_) {
        throw std::invalid_argument("Invalid move: out of turn.");  // todo function
    }

    pieceFrom1->merge(to, pieceFrom2);
    changeTurn_();
    //for debugging
    printBoard();
}

void Board::finishGame(__attribute__((unused)) PieceColor winner) {
    finished_ = true;
}

Piece *Board::getPiece(Position position) const {
    for (const auto &piece : *this) {
        if (piece->getPosition() == position) {
            return piece;
        }
    }
    return nullptr;
}

std::list<Position> Board::getPossibleMoves(Position position) const {
    auto piece = getPiece(position);
    if (piece == nullptr) {
        throw std::invalid_argument("Error: Empty square.");
    }

    return piece->getPossibleMoves();
}

bool Board::isFinished() const {
    return finished_;
}

void Board::changeTurn_() {
    turn_ = turn_ == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
}

void Board::generatePiecesForColor_(PieceColor color) {
    int pawnRank = color == PieceColor::WHITE? 2 : 7;
    for (int i = 1; i <= 8; ++i) {
        pieces_.push_back(new Pawn(color, Position(i, pawnRank), this));
    }

    int rank = color == PieceColor::WHITE ? 1 : 8;
    pieces_.push_back(new Rook(color, Position(1, rank), this));
    pieces_.push_back(new Rook(color, Position(8, rank), this));

    pieces_.push_back(new Knight(color, Position(2, rank), this));
    pieces_.push_back(new Knight(color, Position(7, rank), this));

    pieces_.push_back(new Bishop(color, Position(3, rank), this));
    pieces_.push_back(new Bishop(color, Position(6, rank), this));

    pieces_.push_back(new Queen(color, Position(4, rank), this));

    pieces_.push_back(new King(color, Position(5, rank), this));
}

Board::~Board() {
    for (Piece* piece : pieces_) {
        delete piece;
    }
}

void Board::printBoard() {
    char chessBoard[8][8]{};
    for (const auto &piece : (*this)) {
        chessBoard[piece->getPosition().getY() - 1][piece->getPosition().getX() - 1] = piece->getDrawing();
    }

    for (auto &file : chessBoard) {
        // printf("--------\n");
        for (char square : file) {
            printf("|");
            if (square) {
                printf("%c", square);
            } else {
                printf(" ");
            }
        }
        printf("|");
        printf("\n");
    }
    printf("-----------------\n");
}
