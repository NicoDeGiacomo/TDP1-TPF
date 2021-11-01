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

TEST_SUITE("Moves tests (empty board)") {
TEST_CASE("Possible positions") {
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), nullptr);
    auto whitePositions = whitePawn.getPossiblePositions();
    CHECK_EQ(2, whitePositions.size());
    CHECK(!findPosition_(whitePositions, Position(1, 2)));
    CHECK(findPosition_(whitePositions, Position(1, 3)));
    CHECK(findPosition_(whitePositions, Position(1, 4)));

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), nullptr);
    auto blackPositions = blackPawn.getPossiblePositions();
    CHECK_EQ(2, blackPositions.size());
    CHECK(!findPosition_(blackPositions, Position(1, 7)));
    CHECK(findPosition_(blackPositions, Position(1, 6)));
    CHECK(findPosition_(blackPositions, Position(1, 5)));

    Rook rook(PieceColor::WHITE, Position(1, 1), nullptr);
    auto rookPositions = rook.getPossiblePositions();
    CHECK_EQ(14, rookPositions.size());
    CHECK(!findPosition_(rookPositions, Position(8, 8)));
    CHECK(!findPosition_(rookPositions, Position(1, 1)));
    CHECK(findPosition_(rookPositions, Position(1, 8)));
    CHECK(findPosition_(rookPositions, Position(8, 1)));

    Knight knight(PieceColor::WHITE, Position(1, 1), nullptr);
    auto knightPositions = knight.getPossiblePositions();
    CHECK_EQ(2, knightPositions.size());
    CHECK(findPosition_(knightPositions, Position(2, 3)));
    CHECK(findPosition_(knightPositions, Position(3, 2)));

    Bishop bishop(PieceColor::WHITE, Position(2, 2), nullptr);
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

    Queen queen(PieceColor::WHITE, Position(3, 2), nullptr);
    auto queenPositions = queen.getPossiblePositions();
    CHECK_EQ(23, queenPositions.size());
    CHECK(!findPosition_(queenPositions, Position(3, 2)));
    CHECK(findPosition_(queenPositions, Position(8, 7)));
    CHECK(findPosition_(queenPositions, Position(3, 8)));
    CHECK(findPosition_(queenPositions, Position(8, 2)));

    King king(PieceColor::WHITE, Position(8, 5), nullptr);
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
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), nullptr);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 2)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 5)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(2, 3)), "Invalid move.", std::invalid_argument);

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), nullptr);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 7)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 4)), "Invalid move.", std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(2, 6)), "Invalid move.", std::invalid_argument);
}

TEST_CASE("Valid moves") {
    // todo: implement me!
}
}

TEST_SUITE("Moves tests (default board)") {
TEST_CASE("Possible positions") {
    Board board;
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), &board);
    auto whitePositions = whitePawn.getPossiblePositions();
    CHECK_EQ(2, whitePositions.size());
    CHECK(!findPosition_(whitePositions, Position(1, 2)));
    CHECK(findPosition_(whitePositions, Position(1, 3)));
    CHECK(findPosition_(whitePositions, Position(1, 4)));

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), &board);
    auto blackPositions = blackPawn.getPossiblePositions();
    CHECK_EQ(2, blackPositions.size());
    CHECK(!findPosition_(blackPositions, Position(1, 7)));
    CHECK(findPosition_(blackPositions, Position(1, 6)));
    CHECK(findPosition_(blackPositions, Position(1, 5)));

    Rook rook(PieceColor::WHITE, Position(1, 1), &board);
    auto rookPositions = rook.getPossiblePositions();
    CHECK_EQ(0, rookPositions.size());

    Knight knight(PieceColor::WHITE, Position(2, 1), &board);
    auto knightPositions = knight.getPossiblePositions();
    CHECK_EQ(2, knightPositions.size());
    CHECK(findPosition_(knightPositions, Position(1, 3)));
    CHECK(findPosition_(knightPositions, Position(3, 3)));

    Bishop bishop(PieceColor::WHITE, Position(3, 1), &board);
    auto bishopPositions = bishop.getPossiblePositions();
    CHECK_EQ(0, bishopPositions.size());

    Queen queen(PieceColor::WHITE, Position(4, 1), &board);
    auto queenPositions = queen.getPossiblePositions();
    CHECK_EQ(0, queenPositions.size());

    King king(PieceColor::WHITE, Position(5, 1), &board);
    auto kingPositions = king.getPossiblePositions();
    CHECK_EQ(0, kingPositions.size());
}

TEST_CASE("Valid moves") {
    // todo: implement me!
}
}
