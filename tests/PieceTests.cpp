#include "tests/doctest/doctest.h"
#include "Tests.cpp"

#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

TEST_SUITE("Positions tests") {
TEST_CASE("Valid position") {
    CHECK_NOTHROW(Position(1, 8));
    Position position(1, 8);
    CHECK_EQ(position.getX(), 1);
    CHECK_EQ(position.getY(), 8);
}

TEST_CASE("Invalid position") {
    CHECK_THROWS_WITH_AS(Position(9, 9), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 0), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 9), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(9, 1), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 1), "Invalid position.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 0), "Invalid position.", std::invalid_argument);
}

TEST_CASE("Compare positions") {
    CHECK_EQ(Position(1, 1), Position(1, 1));
    CHECK_EQ(Position(8, 8), Position(8, 8));
    CHECK_EQ(Position(4, 5), Position(4, 5));

    CHECK_NE(Position(1, 1), Position(1, 2));
    CHECK_NE(Position(1, 1), Position(2, 1));
    CHECK_NE(Position(1, 1), Position(2, 2));
    CHECK_NE(Position(1, 2), Position(2, 1));
}
}

TEST_SUITE("Moves tests") {
TEST_CASE("Possible positions") {
    Pawn whitePawn(WHITE, Position(1, 2));
    auto whitePositions = whitePawn.getPossiblePositions();
    CHECK_EQ(2, whitePositions.size());
    CHECK(!findPosition_(whitePositions, Position(1, 2)));
    CHECK(findPosition_(whitePositions, Position(1, 3)));
    CHECK(findPosition_(whitePositions, Position(1, 4)));

    Pawn blackPawn(BLACK, Position(1, 7));
    auto blackPositions = blackPawn.getPossiblePositions();
    CHECK_EQ(2, blackPositions.size());
    CHECK(!findPosition_(blackPositions, Position(1, 7)));
    CHECK(findPosition_(blackPositions, Position(1, 6)));
    CHECK(findPosition_(blackPositions, Position(1, 5)));

    Rook rook(WHITE, Position(1, 1));
    auto rookPositions = rook.getPossiblePositions();
    CHECK_EQ(14, rookPositions.size());
    CHECK(!findPosition_(rookPositions, Position(8, 8)));
    CHECK(!findPosition_(rookPositions, Position(1, 1)));
    CHECK(findPosition_(rookPositions, Position(1, 8)));
    CHECK(findPosition_(rookPositions, Position(8, 1)));

    Knight knight(WHITE, Position(1, 1));
    auto knightPositions = knight.getPossiblePositions();
    CHECK_EQ(2, knightPositions.size());
    CHECK(findPosition_(knightPositions, Position(2, 3)));
    CHECK(findPosition_(knightPositions, Position(3, 2)));

    Bishop bishop(WHITE, Position(2, 2));
    auto bishopPositions = bishop.getPossiblePositions();
    CHECK_EQ(9, bishopPositions.size());
    CHECK(!findPosition_(bishopPositions, Position(2, 2)));
    CHECK(findPosition_(bishopPositions, Position(1, 1)));
    CHECK(findPosition_(bishopPositions, Position(3, 3)));
    CHECK(findPosition_(bishopPositions, Position(4, 4)));
    CHECK(findPosition_(bishopPositions, Position(5, 5)));
    CHECK(findPosition_(bishopPositions, Position(6, 6)));
    CHECK(findPosition_(bishopPositions, Position(7, 7)));
    CHECK(findPosition_(bishopPositions, Position(8, 8)));
    CHECK(findPosition_(bishopPositions, Position(1, 3)));
    CHECK(findPosition_(bishopPositions, Position(3, 1)));

    Queen queen(WHITE, Position(3, 2));
    auto queenPositions = queen.getPossiblePositions();
    CHECK_EQ(23, queenPositions.size());
    CHECK(!findPosition_(queenPositions, Position(3, 2)));
    CHECK(findPosition_(queenPositions, Position(8, 7)));
    CHECK(findPosition_(queenPositions, Position(3, 8)));
    CHECK(findPosition_(queenPositions, Position(8, 2)));

    King king(WHITE, Position(8, 5));
    auto kingPositions = king.getPossiblePositions();
    CHECK_EQ(5, kingPositions.size());
    CHECK(!findPosition_(kingPositions, Position(8, 5)));
    CHECK(findPosition_(kingPositions, Position(8, 6)));
    CHECK(findPosition_(kingPositions, Position(8, 4)));
    CHECK(findPosition_(kingPositions, Position(7, 5)));
    CHECK(findPosition_(kingPositions, Position(7, 6)));
    CHECK(findPosition_(kingPositions, Position(7, 4)));
}

TEST_CASE("Invalid moves") {
    Pawn whitePawn(WHITE, Position(1, 2));
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 2)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 5)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(2, 3)), "Invalid move.", std::invalid_argument);

    Pawn blackPawn(BLACK, Position(1, 7));
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 7)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 4)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(2, 6)), "Invalid move.", std::invalid_argument);
}

TEST_CASE("Valid moves") {
    // todo: implement me!
}
}
