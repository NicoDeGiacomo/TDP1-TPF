#include "Rook.h"

Rook::Rook(PieceColor color, Position position) : Piece(color, position) {}

char Rook::getDrawing() const {
    return 'R';
}
