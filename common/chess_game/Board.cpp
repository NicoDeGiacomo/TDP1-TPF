#include "Board.h"

#include <chess_game/pieces/Pawn.h>

Board::Board() {
    pieces_.push_back(Pawn(WHITE, Position(1, 2)));
    pieces_.push_back(Pawn(WHITE, Position(2, 2)));
    pieces_.push_back(Pawn(WHITE, Position(3, 2)));
    pieces_.push_back(Pawn(WHITE, Position(4, 2)));
    pieces_.push_back(Pawn(WHITE, Position(5, 2)));
    pieces_.push_back(Pawn(WHITE, Position(6, 2)));
    pieces_.push_back(Pawn(WHITE, Position(7, 2)));
    pieces_.push_back(Pawn(WHITE, Position(8, 2)));
}

std::list<Piece>::iterator Board::begin() {
    return pieces_.begin();
}

std::list<Piece>::iterator Board::end() {
    return pieces_.end();
}


