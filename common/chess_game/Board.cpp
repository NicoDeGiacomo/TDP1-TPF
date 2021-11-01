#include "Board.h"

#include <chess_game/pieces/Pawn.h>
#include <chess_game/pieces/Rook.h>
#include <chess_game/pieces/Knight.h>
#include <chess_game/pieces/Bishop.h>
#include <chess_game/pieces/Queen.h>
#include <chess_game/pieces/King.h>
#include <algorithm>

Board::Board() {
    generatePiecesForColor(PieceColor::WHITE);
    generatePiecesForColor(PieceColor::BLACK);
}

std::list<Piece*>::const_iterator Board::begin() const {
    return pieces_.begin();
}

std::list<Piece*>::const_iterator Board::end() const {
    return pieces_.end();
}

Piece *Board::getPiece(Position position) {
    // todo: hacer que pieces_ sea un mapa, para mejor eficiencia?
    for (const auto &piece : *this) {
        if (piece->getPosition() == position) {
            return piece;
        }
    }
    return nullptr;
}

void Board::generatePiecesForColor(PieceColor color) {
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
