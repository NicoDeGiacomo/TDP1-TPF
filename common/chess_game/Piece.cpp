#include "Piece.h"

Piece::Piece(PieceColor color, Position position, char drawing)
    : color_(color), position_(position), drawing_(drawing) {}

char Piece::getDrawing() const {
    return drawing_;
}

Position Piece::getPosition() const {
    return position_;
}
void Piece::move(Position position) {
    position_ = position;
}
