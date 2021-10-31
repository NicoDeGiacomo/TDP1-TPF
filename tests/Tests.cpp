#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <chess_game/pieces/Rook.h>
#include <chess_game/pieces/Knight.h>
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

TEST_CASE("Valid positions") {
    Pawn whitePawn(WHITE, Position(1, 2));
    auto whitePositions = whitePawn.getPossiblePositions();
    CHECK_EQ(2, whitePositions.size());
    CHECK((std::find(whitePositions.begin(), whitePositions.end(), Position(1, 3)) != whitePositions.end()));
    CHECK((std::find(whitePositions.begin(), whitePositions.end(), Position(1, 4)) != whitePositions.end()));
    CHECK((std::find(whitePositions.begin(), whitePositions.end(), Position(1, 2)) == whitePositions.end()));

    Pawn blackPawn(BLACK, Position(1, 7));
    auto blackPositions = blackPawn.getPossiblePositions();
    CHECK_EQ(2, blackPositions.size());
    CHECK((std::find(blackPositions.begin(), blackPositions.end(), Position(1, 6)) != blackPositions.end()));
    CHECK((std::find(blackPositions.begin(), blackPositions.end(), Position(1, 5)) != blackPositions.end()));
    CHECK((std::find(blackPositions.begin(), blackPositions.end(), Position(1, 7)) == blackPositions.end()));

    Rook rook(WHITE, Position(1, 1));
    auto rookPositions = rook.getPossiblePositions();
    CHECK_EQ(14, rookPositions.size());
    CHECK((std::find(rookPositions.begin(), rookPositions.end(), Position(1, 8)) != rookPositions.end()));
    CHECK((std::find(rookPositions.begin(), rookPositions.end(), Position(8, 1)) != rookPositions.end()));
    CHECK((std::find(rookPositions.begin(), rookPositions.end(), Position(8, 8)) == rookPositions.end()));
    CHECK((std::find(rookPositions.begin(), rookPositions.end(), Position(1, 1)) == rookPositions.end()));

    Knight knight(WHITE, Position(1, 1));
    auto knightPositions = knight.getPossiblePositions();
    CHECK_EQ(2, knightPositions.size());
    CHECK((std::find(knightPositions.begin(), knightPositions.end(), Position(2, 3)) != knightPositions.end()));
    CHECK((std::find(knightPositions.begin(), knightPositions.end(), Position(3, 2)) != knightPositions.end()));

    // todo: check pieces left
}

TEST_CASE("Invalid move") {
    Pawn whitePawn(WHITE, Position(1, 2));
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 2)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 5)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(2, 3)), "Invalid move.", std::invalid_argument);

    Pawn blackPawn(BLACK, Position(1, 7));
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 7)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 4)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(2, 6)), "Invalid move.", std::invalid_argument);
}
}

TEST_SUITE("Position tests") {
TEST_CASE("Create valid position") {
    CHECK_NOTHROW(Position(1, 8));
    Position position(1, 8);
    CHECK_EQ(position.getX(), 1);
    CHECK_EQ(position.getY(), 8);
}

TEST_CASE("Create invalid position") {
    CHECK_THROWS_WITH_AS(Position(9, 9), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 0), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 9), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(9, 1), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 1), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 0), "Invalid position.", std::invalid_argument);
}
}
