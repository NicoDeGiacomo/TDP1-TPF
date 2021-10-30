#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tests/doctest/doctest.h"
#include "common/chess_game/Board.h"
#include "common/chess_game/pieces/Pawn.h"

TEST_SUITE("Board tests") {
TEST_CASE("Create Chess Board") {
    Board board;

    unsigned short total = 0;
    unsigned short pawns = 0;
    unsigned short rooks = 0;
    unsigned short knights = 0;
    unsigned short bishops = 0;
    unsigned short queens = 0;
    unsigned short kings = 0;
    for (const Piece& piece : board) {
        total++;
        switch (piece.getDrawing()) {
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
