#include "Bishop.h"

Bishop::Bishop(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

char Bishop::getDrawing() const {
    return 'B';
}

std::list<std::pair<int, int>> Bishop::getVectorBeamMoves_() const {
    return {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Bishop::getVectorStepMoves_() const {
    return {};
}

void Bishop::createSplit_(Position to, float probability) {
    auto* split = new Bishop(color_, position_, board_, probability);
    split->move(to);
    appendToBoard_(split);
}

Bishop::Bishop(PieceColor color,
               Position position,
               Board *board,
               float probability) : Piece(color,
                                          position,
                                          board,
                                          probability) {}
