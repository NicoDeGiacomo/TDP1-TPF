#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "tests/doctest/doctest.h"
#include "common/chess_game/Board.h"
#include "common/chess_game/pieces/Pawn.h"

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

TEST_SUITE("Pieces tests") {
TEST_CASE("Compare positions") {
    CHECK(Position(1, 1) != Position(1, 2));
    CHECK(Position(1, 1) != Position(2, 1));
    CHECK(Position(1, 1) != Position(2, 2));
    CHECK(Position(1, 1) == Position(1, 1));
}

TEST_CASE("Get possible positions") {
    Pawn pawn(WHITE, Position(1, 1));
    auto positions = pawn.getPossiblePositions();
    CHECK_EQ(2, positions.size());

    bool pos1 = (std::find(positions.begin(), positions.end(), Position(1, 2)) != positions.end());
    CHECK(pos1);

    bool pos2 = (std::find(positions.begin(), positions.end(), Position(1, 3)) != positions.end());
    CHECK(pos2);
}

TEST_CASE("Move piece to valid position") {
    // todo: implement me
}
}

TEST_SUITE("Position tests") {
TEST_CASE("Create valid position") {
    Position position(1, 8);
    CHECK_EQ(position.getX(), 1);
    CHECK_EQ(position.getY(), 8);
}

TEST_CASE("Create invalid position") {
    CHECK_THROWS_AS(Position(9, 9), std::invalid_argument);
    CHECK_THROWS_AS(Position(0, 0), std::invalid_argument);
}
}
