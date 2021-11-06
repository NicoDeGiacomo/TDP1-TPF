#include "Board.h"

#include <chess_game/pieces/Pawn.h>
#include <chess_game/pieces/Rook.h>
#include <chess_game/pieces/Knight.h>
#include <chess_game/pieces/Bishop.h>
#include <chess_game/pieces/Queen.h>
#include <chess_game/pieces/King.h>
#include <algorithm>
#include <stdexcept>

Board::Board() : turn_(PieceColor::WHITE), finished_(false) {
    generatePiecesForColor_(PieceColor::WHITE);
    generatePiecesForColor_(PieceColor::BLACK);
}

std::list<Piece*>::const_iterator Board::begin() const {
    return pieces_.begin();
}

std::list<Piece*>::const_iterator Board::end() const {
    return pieces_.end();
}

Piece *Board::getPiece(Position position) const {
    // todo: hacer que pieces_ sea un mapa, para mejor eficiencia?
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
        return {};
    }

    return piece->getPossibleMoves();
}

bool Board::isFinished() const {
    return finished_;
}

void Board::move(Position from, Position to) {
    auto pieceFrom = getPiece(from);
    auto pieceTo = getPiece(to);

    if (pieceFrom == nullptr) {
        throw std::invalid_argument("Invalid move: empty square.");
    }
    if (pieceFrom->getColor() != turn_) {
        throw std::invalid_argument("Invalid move: out of turn.");
    }

    pieceFrom->move(to);

    if (pieceTo != nullptr) {
        pieceTo->eat();
        pieces_.remove(pieceTo);
        delete pieceTo;
    }

    // todo: Promotion

    changeTurn();
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

    pieceFrom->split(to1, to2);
    changeTurn();
}

//void Board::merge(Position pos1, Position pos2) {
//
//}

void Board::finishGame(__attribute__((unused)) PieceColor winner) {
    finished_ = true;
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

void Board::changeTurn() {
    turn_ = turn_ == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE;
}

Board::~Board() {
    for (Piece* piece : pieces_) {
        delete piece;
    }
}
