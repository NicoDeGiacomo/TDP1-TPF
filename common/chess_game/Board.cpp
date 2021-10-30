#include "Board.h"

Board::Board() {
    pieces_.push_back(new Piece(PieceColor::WHITE, Position(0, 0)));
}


