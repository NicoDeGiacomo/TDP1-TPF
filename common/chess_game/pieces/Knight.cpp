#include "Knight.h"

Knight::Knight(PieceColor color, Position position) : Piece(color, position) {}

char Knight::getDrawing() const {
    return 'K';
}
