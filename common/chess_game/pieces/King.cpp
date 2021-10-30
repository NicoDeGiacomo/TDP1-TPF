#include "King.h"

King::King(PieceColor color, Position position) : Piece(color, position) {}

char King::getDrawing() const {
    return 'W';
}


