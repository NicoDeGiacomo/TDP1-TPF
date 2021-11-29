#include "doctest.h"
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
            case 'P':
            case 'p': pawns++;
                break;
            case 'r':
            case 'R': rooks++;
                break;
            case 'n':
            case 'N': knights++;
                break;
            case 'b':
            case 'B': bishops++;
                break;
            case 'q':
            case 'Q': queens++;
                break;
            case 'k':
            case 'K': kings++;
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

    CHECK_EQ(board.getCurrentTurn(), PieceColor::WHITE);
}

TEST_SUITE("Move pieces") {
TEST_CASE("Possible moves") {
    Board board;
    CHECK_EQ(2, board.getPossibleMoves(Position(5, 2)).size());
    CHECK_EQ(0, board.getPossibleMoves(Position(5, 1)).size());
}

TEST_CASE("Invalid move") {
    Board board;
    CHECK_THROWS_WITH_AS(board.move(Position(5, 3), Position(5, 4)),
                         "Invalid move: empty square.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(board.move(Position(5, 2), Position(5, 5)),
                         "Invalid move: not possible.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.getPossibleMoves(Position("e4")),
                         "Error: Empty square.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.move(Position("e7"), Position("e6")),
                         "Invalid move: out of turn.",
                         std::invalid_argument);
}

TEST_CASE("Invalid move - Step on own split") {
    Board board;
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));
    board.split(Position("f1"), Position("d3"), Position("b5"));
    board.move(Position("h7"), Position("h5"));

    CHECK_THROWS_WITH_AS(board.move(Position("d3"), Position("b5"));,
                         "Invalid move: not possible.",
                         std::invalid_argument);
}

TEST_CASE("Capture") {
    Board board;
    CHECK_EQ(32, countPieces_(board));

    board.move(Position(5, 2), Position(5, 4));
    CHECK_EQ(32, countPieces_(board));
    CHECK_EQ(board.getCurrentTurn(), PieceColor::BLACK);

    board.move(Position(4, 7), Position(4, 5));
    CHECK_EQ(32, countPieces_(board));
    CHECK_EQ(board.getCurrentTurn(), PieceColor::WHITE);

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
    CHECK_EQ(32, countPieces_(board));

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
    CHECK_EQ(31, countPieces_(board));
}

TEST_CASE("Finish quantum game - confirm") {
    Board board(false, 1);
    REQUIRE(!board.isFinished());
    REQUIRE_EQ(32, countPieces_(board));

    board.move(Position("f2"), Position("f4"));
    board.move(Position("e7"), Position("e5"));
    board.move(Position("e1"), Position("f2"));
    board.move(Position("d8"), Position("h4"));

    board.split(Position("f2"), Position("g3"), Position("f3"));
    REQUIRE(!board.isFinished());
    REQUIRE_EQ(33, countPieces_(board));

    Piece* queen = board.getPiece(Position("h4"));
    board.move(Position("h4"), Position("g3"));
    REQUIRE(board.isFinished());
    REQUIRE_EQ(31, countPieces_(board));

    CHECK_EQ(board.getPiece(Position("f3")), nullptr);
    CHECK_NE(board.getPiece(Position("g3")), nullptr);
    CHECK_EQ(board.getPiece(Position("g3")), queen);
}

TEST_CASE("Finish quantum game - deny") {
    Board board(false, 3);
    REQUIRE(!board.isFinished());

    board.move(Position("f2"), Position("f4"));
    board.move(Position("e7"), Position("e5"));
    board.move(Position("e1"), Position("f2"));
    board.move(Position("d8"), Position("h4"));

    board.split(Position("f2"), Position("g3"), Position("f3"));
    REQUIRE(!board.isFinished());
    REQUIRE_EQ(33, countPieces_(board));

    Piece* queen = board.getPiece(Position("h4"));
    board.move(Position("h4"), Position("g3"));
    REQUIRE(!board.isFinished());
    REQUIRE_EQ(32, countPieces_(board));

    CHECK_NE(board.getPiece(Position("f3")), nullptr);
    CHECK_EQ(board.getPiece(Position("f3"))->getProbability(), 1.0f);

    CHECK_NE(board.getPiece(Position("g3")), nullptr);
    CHECK_EQ(board.getPiece(Position("g3")), queen);
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

    CHECK_THROWS_WITH_AS(board.split(Position(4, 1),
                                     Position(4, 3),
                                     Position(4, 3)),
                         "Invalid move: equal split positions.",
                         std::invalid_argument);

    CHECK_EQ(32, countPieces_(board));
}

TEST_CASE("Valid split") {
    Board board;
    board.move(Position(3, 2), Position(3, 3));
    board.move(Position(4, 7), Position(4, 6));

    CHECK_EQ(board.getPiece(Position(4, 1))->getProbability(), 1.0);
    board.split(Position(4, 1), Position(3, 2), Position(2, 3));
    CHECK_EQ(33, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(4, 1)), nullptr);
    CHECK_EQ(board.getPiece(Position(3, 2))->getProbability(), 0.5);
    CHECK_EQ(board.getPiece(Position(2, 3))->getProbability(), 0.5);
}

TEST_CASE("Double split") {
    Board board;
    board.move(Position(3, 2), Position(3, 3));
    board.move(Position(4, 7), Position(4, 6));

    CHECK_EQ(board.getPiece(Position(4, 1))->getProbability(), 1.0f);
    board.split(Position(4, 1), Position(3, 2), Position(2, 3));
    CHECK_EQ(33, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(4, 1)), nullptr);
    CHECK_EQ(board.getPiece(Position(3, 2))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position(2, 3))->getProbability(), 0.5f);

    board.move(Position(8, 7), Position(8, 6));
    board.split(Position(2, 3), Position(2, 4), Position(2, 5));
    CHECK_EQ(34, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(2, 3)), nullptr);
    CHECK_EQ(board.getPiece(Position(2, 4))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(2, 5))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(3, 2))->getProbability(), 0.5f);
}

TEST_CASE("Two double splits") {
    Board board;
    board.move(Position(3, 2), Position(3, 3));
    board.move(Position(4, 7), Position(4, 6));

    CHECK_EQ(board.getPiece(Position(4, 1))->getProbability(), 1.0f);
    board.split(Position(4, 1), Position(3, 2), Position(2, 3));
    CHECK_EQ(33, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(4, 1)), nullptr);
    CHECK_EQ(board.getPiece(Position(3, 2))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position(2, 3))->getProbability(), 0.5f);

    board.move(Position(8, 7), Position(8, 6));
    board.split(Position(2, 3), Position(2, 4), Position(2, 5));
    CHECK_EQ(34, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(2, 3)), nullptr);
    CHECK_EQ(board.getPiece(Position(2, 4))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(2, 5))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(3, 2))->getProbability(), 0.5f);

    board.move(Position(8, 6), Position(8, 5));
    board.split(Position(3, 2), Position(4, 3), Position(1, 4));
    CHECK_EQ(35, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(2, 3)), nullptr);
    CHECK_EQ(board.getPiece(Position(2, 4))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(2, 5))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(4, 3))->getProbability(), 0.25f);
    CHECK_EQ(board.getPiece(Position(1, 4))->getProbability(), 0.25f);
}
}

TEST_SUITE("Merge") {
TEST_CASE("Invalid merge") {
    Board board;
    CHECK_THROWS_WITH_AS(board.merge(Position("e2"),
                                     Position("e2"),
                                     Position("e3")),
                         "Invalid move: merging same position.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.merge(Position("e3"),
                                     Position("e4"),
                                     Position("e5")),
                         "Invalid move: empty square.",
                         std::invalid_argument);

    CHECK_THROWS_WITH_AS(board.merge(Position("e2"),
                                     Position("d2"),
                                     Position("e3")),
                         "Invalid move: cannot merge a pawn.",
                         std::invalid_argument);

    CHECK_EQ(32, countPieces_(board));
}

TEST_CASE("Valid merge - empty square") {
    Board board;
    board.move(Position(3, 2), Position(3, 3));
    board.move(Position(4, 7), Position(4, 6));
    board.split(Position(4, 1), Position(3, 2), Position(2, 3));
    board.move(Position(4, 6), Position(4, 5));

    board.merge(Position(3, 2), Position(2, 3), Position(4, 1));
    CHECK_EQ(32, countPieces_(board));

    CHECK_EQ(board.getPiece(Position(3, 2)), nullptr);
    CHECK_EQ(board.getPiece(Position(2, 3)), nullptr);
    CHECK_NE(board.getPiece(Position(4, 1)), nullptr);
    CHECK_EQ(board.getPiece(Position(4, 1))->getProbability(), 1.0);
}

TEST_CASE("Valid merge - non empty square") {
    SUBCASE("Case 1") {
        Board board;
        board.move(Position(3, 2), Position(3, 3));
        board.move(Position(4, 7), Position(4, 6));
        board.split(Position(4, 1), Position(3, 2), Position(2, 3));
        board.move(Position(4, 6), Position(4, 5));

        board.merge(Position(3, 2), Position(2, 3), Position(2, 3));
        CHECK_EQ(32, countPieces_(board));

        CHECK_EQ(board.getPiece(Position(3, 2)), nullptr);
        CHECK_EQ(board.getPiece(Position(4, 1)), nullptr);
        CHECK_NE(board.getPiece(Position(2, 3)), nullptr);
        CHECK_EQ(board.getPiece(Position(2, 3))->getProbability(), 1.0);
    }

    SUBCASE("Case 2") {
        Board board;
        board.move(Position("c2"), Position("c3"));
        board.move(Position("d7"), Position("d6"));
        board.split(Position("d1"), Position("c2"), Position("b3"));
        board.move(Position("d6"), Position("d5"));

        board.merge(Position("c2"), Position("b3"), Position("c2"));
        CHECK_EQ(32, countPieces_(board));

        CHECK_EQ(board.getPiece(Position("b3")), nullptr);
        CHECK_EQ(board.getPiece(Position("d1")), nullptr);
        CHECK_NE(board.getPiece(Position("c2")), nullptr);
        CHECK_EQ(board.getPiece(Position("c2"))->getProbability(), 1.0);
    }
}

TEST_CASE("Double split and merge") {
    Board board;
    board.move(Position("c2"), Position("c3"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("c2"), Position("b3"));
    board.move(Position("h7"), Position("h6"));
    board.split(Position("b3"), Position("b4"), Position("a4"));
    board.move(Position("h6"), Position("h5"));

    board.merge(Position("b4"), Position("c2"), Position("b3"));
    board.move(Position("h5"), Position("h4"));

    CHECK_EQ(33, countPieces_(board));
    CHECK_EQ(board.getPiece(Position("b4")), nullptr);
    CHECK_EQ(board.getPiece(Position("c2")), nullptr);
    CHECK_NE(board.getPiece(Position("b3")), nullptr);
    CHECK_NE(board.getPiece(Position("a4")), nullptr);
    CHECK_EQ(board.getPiece(Position("b3"))->getProbability(), 0.75f);
    CHECK_EQ(board.getPiece(Position("a4"))->getProbability(), 0.25f);

    board.merge(Position("b3"), Position("a4"), Position("a4"));

    CHECK_EQ(32, countPieces_(board));
    CHECK_EQ(board.getPiece(Position("b3")), nullptr);
    CHECK_NE(board.getPiece(Position("a4")), nullptr);
    CHECK_EQ(board.getPiece(Position("a4"))->getProbability(), 1.0f);
}
}

TEST_SUITE("Measurements") {
TEST_CASE("Eating split - Eaten piece 0.5 - confirm") {
    Board board(false, 1);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("b5"), Position("a6"));
    REQUIRE_EQ(33, countPieces_(board));

    Piece* pieceInB7 = board.getPiece(Position("b7"));
    board.move(Position("b7"), Position("a6"));

    REQUIRE_EQ(31, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("a6")), nullptr);
    CHECK_EQ(board.getPiece(Position("a6")), pieceInB7);

    CHECK_EQ(board.getPiece(Position("b7")), nullptr);
    CHECK_EQ(board.getPiece(Position("b5")), nullptr);
    CHECK_EQ(board.getPiece(Position("f1")), nullptr);
}

TEST_CASE("Eating split - Moved piece 0.5 - confirm") {
    Board board(false, 1);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("c4"), Position("b5"));
    board.move(Position("f7"), Position("f6"));
    REQUIRE_EQ(33, countPieces_(board));

    Piece* bishop = board.getPiece(Position("c4"));
    board.move(Position("c4"), Position("g8"));

    REQUIRE_EQ(31, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("g8")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("c4")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("b5")), nullptr);

    CHECK_EQ(board.getPiece(Position("g8")), bishop);
    CHECK_EQ(board.getPiece(Position("g8"))->getProbability(), 1.0f);
}

TEST_CASE("Eating split - Both pieces 0.5 - confirm") {
    Board board(false, 2);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d5"));

    board.split(Position("f1"), Position("c4"), Position("b5"));
    board.split(Position("d8"), Position("d7"), Position("d6"));
    REQUIRE_EQ(34, countPieces_(board));

    Piece* bishop = board.getPiece(Position("b5"));
    board.move(Position("b5"), Position("d7"));

    REQUIRE_EQ(31, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("d7")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("c4")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("b5")), nullptr);

    CHECK_EQ(board.getPiece(Position("d7")), bishop);
    CHECK_EQ(board.getPiece(Position("d7"))->getProbability(), 1.0f);
}

TEST_CASE("Eating split - Eaten piece 0.5 - deny") {
    Board board(false, 3);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("b5"), Position("a6"));
    REQUIRE_EQ(33, countPieces_(board));

    Piece* pieceInB7 = board.getPiece(Position("b7"));
    board.move(Position("b7"), Position("a6"));

    REQUIRE_EQ(32, countPieces_(board));
    REQUIRE_EQ(board.getPiece(Position("a6")), nullptr);
    REQUIRE_NE(board.getPiece(Position("b7")), nullptr);
    CHECK_EQ(board.getPiece(Position("b7")), pieceInB7);

    CHECK_EQ(board.getPiece(Position("f1")), nullptr);
    CHECK_NE(board.getPiece(Position("b5")), nullptr);
}

TEST_CASE("Eating split - Moved piece 0.5 - deny") {
    Board board(false, 3);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("c4"), Position("b5"));
    board.move(Position("f7"), Position("f6"));
    REQUIRE_EQ(33, countPieces_(board));

    Piece* knight = board.getPiece(Position("g8"));
    board.move(Position("c4"), Position("g8"));

    REQUIRE_EQ(32, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("g8")), nullptr);
    REQUIRE_NE(board.getPiece(Position("b5")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("c4")), nullptr);

    CHECK_EQ(board.getPiece(Position("g8")), knight);
    CHECK_EQ(board.getPiece(Position("g8"))->getProbability(), 1.0f);

    CHECK_EQ(board.getPiece(Position("b5"))->getProbability(), 1.0f);
}

TEST_CASE("Eating split - Both pieces 0.5 - deny - case 1") {
    Board board(false, 3);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d5"));

    board.split(Position("f1"), Position("c4"), Position("b5"));
    board.split(Position("d8"), Position("d7"), Position("d6"));
    REQUIRE_EQ(34, countPieces_(board));

    board.move(Position("b5"), Position("d7"));

    REQUIRE_EQ(33, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("d7")), nullptr);
    REQUIRE_NE(board.getPiece(Position("d6")), nullptr);
    REQUIRE_NE(board.getPiece(Position("c4")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("b5")), nullptr);

    CHECK_EQ(board.getPiece(Position("c4"))->getProbability(), 1.0f);
    CHECK_EQ(board.getPiece(Position("d7"))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position("d6"))->getProbability(), 0.5f);
}

TEST_CASE("Eating split - Both pieces 0.5 - deny - case 2") {
    Board board(false, 1);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d5"));

    board.split(Position("f1"), Position("c4"), Position("b5"));
    board.split(Position("d8"), Position("d7"), Position("d6"));
    REQUIRE_EQ(34, countPieces_(board));

    board.move(Position("b5"), Position("d7"));

    REQUIRE_EQ(32, countPieces_(board));
    REQUIRE_NE(board.getPiece(Position("d7")), nullptr);
    REQUIRE_NE(board.getPiece(Position("d6")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("b5")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("c4")), nullptr);

    CHECK_EQ(board.getPiece(Position("d7"))->getProbability(), 1.0f);
    CHECK_EQ(board.getPiece(Position("d6"))->getProbability(), 1.0f);
}

TEST_CASE("Double split and Measurement - Confirm - 25%") {
    Board board(false, 5);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("e2"), Position("d3"));
    REQUIRE_EQ(33, countPieces_(board));

    board.move(Position("h7"), Position("h6"));
    board.split(Position("d3"), Position("b5"), Position("a6"));
    REQUIRE_EQ(34, countPieces_(board));

    Piece* b7Pawn = board.getPiece(Position("b7"));
    board.move(Position("b7"), Position("a6"));

    REQUIRE_EQ(31, countPieces_(board));
    CHECK_NE(board.getPiece(Position("a6")), nullptr);
    CHECK_EQ(board.getPiece(Position("a6"))->getProbability(), 1.0f);
    CHECK_EQ(board.getPiece(Position("a6")), b7Pawn);
    CHECK_EQ(board.getPiece(Position("e2")), nullptr);
    CHECK_EQ(board.getPiece(Position("d3")), nullptr);
    CHECK_EQ(board.getPiece(Position("b5")), nullptr);
}

TEST_CASE("Double split and Measurement - Deny - 25%") {
    Board board(false, 17);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("e2"), Position("d3"));
    REQUIRE_EQ(33, countPieces_(board));

    board.move(Position("h7"), Position("h6"));
    board.split(Position("d3"), Position("b5"), Position("a6"));
    REQUIRE_EQ(34, countPieces_(board));

    board.move(Position("b7"), Position("a6"));

    REQUIRE_EQ(33, countPieces_(board));
    REQUIRE_EQ(board.getPiece(Position("a6")), nullptr);
    REQUIRE_NE(board.getPiece(Position("b7")), nullptr);

    CHECK_NE(board.getPiece(Position("e2")), nullptr);
    CHECK_EQ(board.getPiece(Position("e2"))->getProbability(), 0.5f);
    CHECK_NE(board.getPiece(Position("b5")), nullptr);
    CHECK_EQ(board.getPiece(Position("b5"))->getProbability(), 0.5f);
}

TEST_CASE("Double split and Measurement - Confirm - 50%") {
    Board board(false, 2);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("e2"), Position("a6"));
    REQUIRE_EQ(33, countPieces_(board));

    board.move(Position("h7"), Position("h6"));
    board.split(Position("e2"), Position("b5"), Position("c4"));
    REQUIRE_EQ(34, countPieces_(board));

    Piece* b7Pawn = board.getPiece(Position("b7"));
    board.move(Position("b7"), Position("a6"));

    REQUIRE_EQ(31, countPieces_(board));
    CHECK_NE(board.getPiece(Position("a6")), nullptr);
    CHECK_EQ(board.getPiece(Position("a6"))->getProbability(), 1.0f);
    CHECK_EQ(board.getPiece(Position("a6")), b7Pawn);
    CHECK_EQ(board.getPiece(Position("b5")), nullptr);
    CHECK_EQ(board.getPiece(Position("c4")), nullptr);
}

TEST_CASE("Double split and Measurement - Deny - 50%") {
    Board board(false, 3);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("e2"), Position("a6"));
    REQUIRE_EQ(33, countPieces_(board));

    board.move(Position("h7"), Position("h6"));
    board.split(Position("e2"), Position("b5"), Position("c4"));
    REQUIRE_EQ(34, countPieces_(board));
    CHECK_NE(board.getPiece(Position("b5")), nullptr);
    CHECK_EQ(board.getPiece(Position("b5"))->getProbability(), 0.25f);
    CHECK_NE(board.getPiece(Position("c4")), nullptr);
    CHECK_EQ(board.getPiece(Position("c4"))->getProbability(), 0.25f);

    board.move(Position("b7"), Position("a6"));
    REQUIRE_EQ(33, countPieces_(board));
    REQUIRE_EQ(board.getPiece(Position("a6")), nullptr);
    REQUIRE_NE(board.getPiece(Position("b7")), nullptr);

    CHECK_NE(board.getPiece(Position("b5")), nullptr);
    CHECK_EQ(board.getPiece(Position("b5"))->getProbability(), 0.5f);
    CHECK_NE(board.getPiece(Position("c4")), nullptr);
    CHECK_EQ(board.getPiece(Position("c4"))->getProbability(), 0.5f);
}
}

TEST_SUITE("Entanglements") {
TEST_CASE("Possible moves allows entanglement with opponent piece") {
    Board board;
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("f3"), Position("g4"));

    auto bishopPositions = board.getPossibleMoves(Position("c8"));
    CHECK_EQ(5, bishopPositions.size());
    CHECK(findPosition_(bishopPositions, Position("h3")));
}

TEST_CASE("Possible moves allows entanglement with own piece") {
    Board board;
    board.move(Position("e2"), Position("e4"));
    board.move(Position("e7"), Position("e5"));

    board.split(Position("f1"), Position("e2"), Position("d3"));

    auto queenPositions = board.getPossibleMoves(Position("d1"));
    CHECK_EQ(3, queenPositions.size());
    CHECK(findPosition_(queenPositions, Position("h5")));
}

TEST_CASE("Entanglement with opponent piece") {
    Board board;
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("f3"), Position("g4"));
    REQUIRE_EQ(33, countPieces_(board));
    board.move(Position("c8"), Position("h3"));
    REQUIRE_EQ(34, countPieces_(board));

    CHECK_NE(board.getPiece(Position("c8")), nullptr);
    CHECK_EQ(board.getPiece(Position("c8"))->getProbability(), 0.5f);
    CHECK_NE(board.getPiece(Position("h3")), nullptr);
    CHECK_EQ(board.getPiece(Position("h3"))->getProbability(), 0.5f);

    CHECK(findPosition_(board.getPiece(Position("h3"))->getEntanglements(), Position("g4")));
    CHECK(findPosition_(board.getPiece(Position("g4"))->getEntanglements(), Position("h3")));
}

TEST_CASE("Entanglement with own piece") {
    Board board;
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("e2"), Position("f3"));
    REQUIRE_EQ(33, countPieces_(board));
    board.move(Position("d6"), Position("d5"));
    board.move(Position("f1"), Position("d3"));
    REQUIRE_EQ(34, countPieces_(board));

    REQUIRE_NE(board.getPiece(Position("e2")), nullptr);
    REQUIRE_NE(board.getPiece(Position("f3")), nullptr);
    REQUIRE_NE(board.getPiece(Position("f1")), nullptr);
    REQUIRE_NE(board.getPiece(Position("d3")), nullptr);

    CHECK_EQ(board.getPiece(Position("e2"))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position("f3"))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position("f1"))->getProbability(), 0.5f);
    CHECK_EQ(board.getPiece(Position("d3"))->getProbability(), 0.5f);

    CHECK(findPosition_(board.getPiece(Position("d3"))->getEntanglements(), Position("e2")));
    CHECK(findPosition_(board.getPiece(Position("e2"))->getEntanglements(), Position("d3")));
}

TEST_CASE("Entanglement with opponent piece - confirm") {
    Board board(false, 1);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("f3"), Position("g4"));
    REQUIRE_EQ(33, countPieces_(board));
    board.move(Position("c8"), Position("h3"));
    REQUIRE_EQ(34, countPieces_(board));

    board.move(Position("g2"), Position("h3"));
    REQUIRE_EQ(board.getPiece(Position("c8")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("g4")), nullptr);
    REQUIRE_NE(board.getPiece(Position("f3")), nullptr);
    REQUIRE_NE(board.getPiece(Position("h3")), nullptr);

    CHECK_EQ(board.getPiece(Position("f3"))->getProbability(), 1.0f);
}

TEST_CASE("Entanglement with opponent piece - deny") {
    Board board(false, 3);
    board.move(Position("e2"), Position("e4"));
    board.move(Position("d7"), Position("d6"));

    board.split(Position("d1"), Position("f3"), Position("g4"));
    REQUIRE_EQ(33, countPieces_(board));
    board.move(Position("c8"), Position("h3"));
    REQUIRE_EQ(34, countPieces_(board));

    board.move(Position("g2"), Position("h3"));
    REQUIRE_EQ(board.getPiece(Position("h3")), nullptr);
    REQUIRE_EQ(board.getPiece(Position("f3")), nullptr);
    REQUIRE_NE(board.getPiece(Position("g4")), nullptr);
    REQUIRE_NE(board.getPiece(Position("c8")), nullptr);

    CHECK_EQ(board.getPiece(Position("g4"))->getProbability(), 1.0f);
    CHECK_EQ(board.getPiece(Position("c8"))->getProbability(), 1.0f);
}

TEST_CASE("Entanglement with opponent piece - confirm") {
    // todo
}

TEST_CASE("Entanglement with opponent piece - deny") {
    // todo
}
}
