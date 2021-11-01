#include "tests/doctest/doctest.h"
#include "Tests.cpp"

#include "Board.h"

TEST_SUITE("Board initialization") {
TEST_CASE("Create Chess Board") {
    Board board;

    int total = 0, rooks = 0, pawns = 0, knights = 0, bishops = 0, queens = 0,
        kings = 0;
    for (auto piece: board) {
        total++;
        switch (piece->getDrawing()) {
            case 'p': pawns++;
                break;
            case 'R': rooks++;
                break;
            case 'K': knights++;
                break;
            case 'B': bishops++;
                break;
            case 'Q': queens++;
                break;
            case 'W': kings++;
                break;
        }
    }
    CHECK_EQ(32, total);
    CHECK_EQ(16, pawns);
    CHECK_EQ(4, rooks);
    CHECK_EQ(4, knights);
    CHECK_EQ(4, bishops);
    CHECK_EQ(2, queens);
    CHECK_EQ(2, kings);
}

TEST_SUITE("Move pieces") {
TEST_CASE("Invalid move") {

}

TEST_CASE("Capture") {
    Board board;
    CHECK_EQ(32, countPieces_(board));

    board.move(Position(5, 2), Position(5, 4));
    CHECK_EQ(32, countPieces_(board));

    board.move(Position(4, 7), Position(4, 5));
    CHECK_EQ(32, countPieces_(board));

    board.move(Position(5, 4), Position(4, 5));
    CHECK_EQ(31, countPieces_(board));

    board.move(Position(4, 8), Position(4, 5));
    CHECK_EQ(30, countPieces_(board));
}

TEST_CASE("Coronation") {

}
}
}
