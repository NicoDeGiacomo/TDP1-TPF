#include "Queen.h"

Queen::Queen(PieceColor color, Position position) : Piece(color, position) {}

char Queen::getDrawing() const {
    return 'Q';
}
