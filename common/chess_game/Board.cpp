#include "Board.h"

#include <chess_game/pieces/Pawn.h>
#include <chess_game/pieces/Rook.h>
#include <chess_game/pieces/Knight.h>
#include <chess_game/pieces/Bishop.h>
#include <chess_game/pieces/Queen.h>
#include <chess_game/pieces/King.h>

Board::Board() {
    generatePiecesForColor(WHITE);
    generatePiecesForColor(BLACK);
}

std::list<Piece>::iterator Board::begin() {
    return pieces_.begin();
}

std::list<Piece>::iterator Board::end() {
    return pieces_.end();
}

void Board::generatePiecesForColor(PieceColor color) {
    unsigned short pawnRank = color == WHITE? 2 : 7;
    for (int i = 1; i <= 8; ++i) {
        pieces_.push_back(Pawn(color, Position(i, pawnRank)));
    }

    unsigned short pieceRank = color == WHITE? 1 : 8;
    pieces_.push_back(Rook(color, Position(1, pieceRank)));
    pieces_.push_back(Rook(color, Position(8, pieceRank)));

    pieces_.push_back(Knight(color, Position(2, pieceRank)));
    pieces_.push_back(Knight(color, Position(7, pieceRank)));

    pieces_.push_back(Bishop(color, Position(3, pieceRank)));
    pieces_.push_back(Bishop(color, Position(6, pieceRank)));

    pieces_.push_back(Queen(color, Position(4, pieceRank)));

    pieces_.push_back(King(color, Position(5, pieceRank)));
}
