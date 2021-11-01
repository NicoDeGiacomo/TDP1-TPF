#include "tests/doctest/doctest.h"
#include "Tests.cpp"

#include "Board.h"

TEST_SUITE("Board tests") {
TEST_CASE("Create Chess Board") {
    Board board;

    int total = 0;
    int pawns = 0;
    int rooks = 0;
    int knights = 0;
    int bishops = 0;
    int queens = 0;
    int kings = 0;
    for (const Piece* piece : board) {
        total++;
        switch (piece->getDrawing()) {
            case 'p': pawns++; break;
            case 'R': rooks++; break;
            case 'K': knights++; break;
            case 'B': bishops++; break;
            case 'Q': queens++; break;
            case 'W': kings++; break;
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
}
