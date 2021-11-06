#include "tests/doctest/doctest.h"
#include "Tests.cpp"  // NOLINT [build/c++11]

#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

TEST_SUITE("Moves tests (empty board)") {
TEST_CASE("Possible positions") {
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), nullptr);
    auto whitePositions = whitePawn.getPossibleMoves();
    CHECK_EQ(2, whitePositions.size());
    CHECK(!findPosition_(whitePositions, Position(1, 2)));
    CHECK(findPosition_(whitePositions, Position(1, 3)));
    CHECK(findPosition_(whitePositions, Position(1, 4)));

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), nullptr);
    auto blackPositions = blackPawn.getPossibleMoves();
    CHECK_EQ(2, blackPositions.size());
    CHECK(!findPosition_(blackPositions, Position(1, 7)));
    CHECK(findPosition_(blackPositions, Position(1, 6)));
    CHECK(findPosition_(blackPositions, Position(1, 5)));

    Rook rook(PieceColor::WHITE, Position(1, 1), nullptr);
    auto rookPositions = rook.getPossibleMoves();
    CHECK_EQ(14, rookPositions.size());
    CHECK(!findPosition_(rookPositions, Position(8, 8)));
    CHECK(!findPosition_(rookPositions, Position(1, 1)));
    CHECK(findPosition_(rookPositions, Position(1, 8)));
    CHECK(findPosition_(rookPositions, Position(8, 1)));

    Knight knight(PieceColor::WHITE, Position(1, 1), nullptr);
    auto knightPositions = knight.getPossibleMoves();
    CHECK_EQ(2, knightPositions.size());
    CHECK(findPosition_(knightPositions, Position(2, 3)));
    CHECK(findPosition_(knightPositions, Position(3, 2)));

    Bishop bishop(PieceColor::WHITE, Position(2, 2), nullptr);
    auto bishopPositions = bishop.getPossibleMoves();
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
    auto queenPositions = queen.getPossibleMoves();
    CHECK_EQ(23, queenPositions.size());
    CHECK(!findPosition_(queenPositions, Position(3, 2)));
    CHECK(findPosition_(queenPositions, Position(8, 7)));
    CHECK(findPosition_(queenPositions, Position(3, 8)));
    CHECK(findPosition_(queenPositions, Position(8, 2)));

    King king(PieceColor::WHITE, Position(8, 5), nullptr);
    auto kingPositions = king.getPossibleMoves();
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
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 2)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(1, 5)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(whitePawn.move(Position(2, 3)),
                         "Invalid move: not possible.",
                         std::invalid_argument);

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), nullptr);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 7)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(1, 4)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(blackPawn.move(Position(2, 6)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
}

TEST_CASE("Valid moves") {
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), nullptr);
    CHECK_EQ(2, whitePawn.getPossibleMoves().size());

    whitePawn.move(Position(1, 3));
    CHECK_EQ(1, whitePawn.getPossibleMoves().size());
    CHECK_EQ(Position(1, 3), whitePawn.getPosition());

    whitePawn.move(Position(1, 4));
    CHECK_EQ(1, whitePawn.getPossibleMoves().size());
    CHECK_EQ(Position(1, 4), whitePawn.getPosition());

    Pawn blackPawn(PieceColor::WHITE, Position(1, 2), nullptr);
    CHECK_EQ(2, blackPawn.getPossibleMoves().size());

    blackPawn.move(Position(1, 4));
    CHECK_EQ(1, blackPawn.getPossibleMoves().size());
    CHECK_EQ(Position(1, 4), blackPawn.getPosition());
}
}

TEST_SUITE("Moves tests (default board)") {
TEST_CASE("Possible positions") {
    Board board;
    Pawn whitePawn(PieceColor::WHITE, Position(1, 2), &board);
    auto whitePositions = whitePawn.getPossibleMoves();
    CHECK_EQ(2, whitePositions.size());
    CHECK(!findPosition_(whitePositions, Position(1, 2)));
    CHECK(findPosition_(whitePositions, Position(1, 3)));
    CHECK(findPosition_(whitePositions, Position(1, 4)));

    Pawn blackPawn(PieceColor::BLACK, Position(1, 7), &board);
    auto blackPositions = blackPawn.getPossibleMoves();
    CHECK_EQ(2, blackPositions.size());
    CHECK(!findPosition_(blackPositions, Position(1, 7)));
    CHECK(findPosition_(blackPositions, Position(1, 6)));
    CHECK(findPosition_(blackPositions, Position(1, 5)));

    Rook rook(PieceColor::WHITE, Position(1, 1), &board);
    auto rookPositions = rook.getPossibleMoves();
    CHECK_EQ(0, rookPositions.size());

    Knight knight(PieceColor::WHITE, Position(2, 1), &board);
    auto knightPositions = knight.getPossibleMoves();
    CHECK_EQ(2, knightPositions.size());
    CHECK(findPosition_(knightPositions, Position(1, 3)));
    CHECK(findPosition_(knightPositions, Position(3, 3)));

    Bishop bishop(PieceColor::WHITE, Position(3, 1), &board);
    auto bishopPositions = bishop.getPossibleMoves();
    CHECK_EQ(0, bishopPositions.size());

    Queen queen(PieceColor::WHITE, Position(4, 1), &board);
    auto queenPositions = queen.getPossibleMoves();
    CHECK_EQ(0, queenPositions.size());

    King king(PieceColor::WHITE, Position(5, 1), &board);
    auto kingPositions = king.getPossibleMoves();
    CHECK_EQ(0, kingPositions.size());
}

TEST_CASE("Valid moves") {
    SUBCASE("Pawn") {
        Board board;
        Pawn whitePawn(PieceColor::WHITE, Position(1, 5), &board);
        whitePawn.move(Position(1, 6));

        CHECK_EQ(1, whitePawn.getPossibleMoves().size());

        whitePawn.move(Position(2, 7));
        CHECK_EQ(2, whitePawn.getPossibleMoves().size());

        whitePawn.move(Position(1, 8));
        CHECK_EQ(0, whitePawn.getPossibleMoves().size());
    }

    SUBCASE("Rook") {
        Board board;
        Rook rook(PieceColor::BLACK, Position(4, 6), &board);
        CHECK_EQ(11, rook.getPossibleMoves().size());

        rook.move(Position(4, 2));
        CHECK_EQ(7, rook.getPossibleMoves().size());
    }

    SUBCASE("Knight") {
        Board board;
        Knight knight(PieceColor::BLACK, Position(2, 8), &board);
        CHECK_EQ(2, knight.getPossibleMoves().size());

        knight.move(Position(3, 6));
        CHECK_EQ(4, knight.getPossibleMoves().size());

        knight.move(Position(4, 4));
        CHECK_EQ(8, knight.getPossibleMoves().size());
    }

    SUBCASE("Bishop") {
        Board board;
        Bishop bishop(PieceColor::BLACK, Position(8, 6), &board);
        CHECK_EQ(4, bishop.getPossibleMoves().size());

        bishop.move(Position(4, 2));
        CHECK_EQ(9, bishop.getPossibleMoves().size());
    }

    SUBCASE("Queen") {
        Board board;
        Queen queen(PieceColor::BLACK, Position(4, 8), &board);
        CHECK_EQ(0, queen.getPossibleMoves().size());
    }

    SUBCASE("King") {
        Board board;
        King king(PieceColor::BLACK, Position(5, 8), &board);
        CHECK_EQ(0, king.getPossibleMoves().size());
    }
}
}
