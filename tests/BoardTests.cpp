#include "tests/doctest/doctest.h"
#include "Tests.cpp"  // NOLINT [build/c++11]

#include "Board.h"

TEST_SUITE("Board tests") {
TEST_CASE("Create Chess Board") {
    Board board;

    int total = 0, rooks = 0, pawns = 0, knights = 0, bishops = 0, queens = 0,
        kings = 0;
    for (auto piece : board) {
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
    Board board;
    CHECK_THROWS_WITH_AS(board.move(Position(5, 3), Position(5, 4)),
                         "Invalid move: empty square.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(board.move(Position(5, 2), Position(5, 5)),
                         "Invalid move: not possible.",
                         std::invalid_argument);
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

    board.move(Position(2, 1), Position(3, 3));
    CHECK_EQ(30, countPieces_(board));

    board.move(Position(5, 7), Position(5, 6));
    CHECK_EQ(30, countPieces_(board));

    board.move(Position(3, 3), Position(4, 5));
    CHECK_EQ(29, countPieces_(board));

    board.move(Position(5, 6), Position(4, 5));
    CHECK_EQ(28, countPieces_(board));
}

TEST_CASE("Promotion") {
    Board board;
    board.move(Position(1, 2), Position(1, 4));
    board.move(Position(8, 7), Position(8, 5));
    board.move(Position(1, 4), Position(1, 5));
    board.move(Position(8, 5), Position(8, 4));
    board.move(Position(1, 5), Position(1, 6));
    board.move(Position(8, 4), Position(8, 3));
    CHECK_EQ(32, countPieces_(board));

    board.move(Position(1, 6), Position(2, 7));
    board.move(Position(8, 3), Position(7, 2));
    CHECK_EQ(30, countPieces_(board));

    board.move(Position(2, 7), Position(1, 8));
    board.move(Position(7, 2), Position(8, 1));
    CHECK_EQ(28, countPieces_(board));

    // todo
    // CHECK_EQ(board.getPiece(Position(1, 8))->getDrawing(), 'Q');
    // CHECK_EQ(board.getPiece(Position(8, 1))->getDrawing(), 'Q');
}

TEST_CASE("Finish game") {
    Board board;
    CHECK(!board.isFinished());

    board.move(Position(3, 2), Position(3, 3));
    CHECK(!board.isFinished());

    board.move(Position(4, 7), Position(4, 6));
    CHECK(!board.isFinished());

    board.move(Position(4, 1), Position(1, 4));
    CHECK(!board.isFinished());

    board.move(Position(8, 7), Position(8, 6));
    CHECK(!board.isFinished());

    board.move(Position(1, 4), Position(5, 8));
    CHECK(board.isFinished());
}
}
}

TEST_SUITE("Split") {
TEST_CASE("Invalid split") {
    Board board;

    CHECK_THROWS_WITH_AS(board.split(Position(5, 5),
                                     Position(1, 3),
                                     Position(1, 4)),
                         "Invalid move: empty square.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.split(Position(1, 2),
                                     Position(2, 2),
                                     Position(1, 4)),
                         "Invalid move: non-empty square.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.split(Position(1, 2),
                                     Position(1, 3),
                                     Position(2, 2)),
                         "Invalid move: non-empty square.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.split(Position(1, 2),
                                     Position(1, 3),
                                     Position(1, 4)),
                         "Invalid move: cannot split a pawn.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.split(Position(4, 1),
                                     Position(4, 3),
                                     Position(4, 4)),
                         "Invalid move: not possible.",
                         std::invalid_argument);

    CHECK_EQ(32, countPieces_(board));
}

TEST_CASE("Valid split") {
    Board board;
    board.move(Position(3, 2), Position(3, 3));
    board.move(Position(4, 7), Position(4, 6));
    board.split(Position(4, 1), Position(3, 2), Position(2, 3));
    CHECK_EQ(33, countPieces_(board));
}
}
