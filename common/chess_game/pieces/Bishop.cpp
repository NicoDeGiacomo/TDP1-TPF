#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position position) : Piece(color, position) {}

char Bishop::getDrawing() const {
    return 'B';
}
