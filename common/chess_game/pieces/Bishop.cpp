#include "Bishop.h"

#include <utility>

Bishop::Bishop(PieceColor color, Position position, Board* board) : Piece(color, position, board) {}

Bishop::Bishop(PieceColor color, Position position, Board* board, std::shared_ptr<PieceSplits> splits) : Piece(color, position, board, std::move(splits)) {}

char Bishop::getDrawing() const {
    return 'B';
}

std::list<std::pair<int, int>> Bishop::getVectorBeamMoves_() const {
    return {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
}

std::list<std::pair<int, int>> Bishop::getVectorStepMoves_() const {
    return {};
}

Piece * Bishop::createSplit_(Position to) {
    return new Bishop(color_, to, board_, splits_);
}
