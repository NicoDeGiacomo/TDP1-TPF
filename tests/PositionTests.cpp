#include "tests/doctest/doctest.h"
#include "Tests.cpp"  // NOLINT [build/c++11]

TEST_SUITE("Positions tests") {
TEST_CASE("Valid position") {
    CHECK_NOTHROW(Position(1, 8));
    Position position(1, 8);
    CHECK_EQ(position.getX(), 1);
    CHECK_EQ(position.getY(), 8);
}

TEST_CASE("Invalid position") {
    CHECK_THROWS_WITH_AS(Position(9, 9),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 0),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 9),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(9, 1),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(0, 1),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position(1, 0),
                         "Invalid position.",
                         std::invalid_argument);
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

TEST_SUITE("Positions tests (algebraic notation)") {
TEST_CASE("Valid position") {
    CHECK_NOTHROW(Position("a8"));
    Position position("a8");
    CHECK_EQ(position.getX(), 1);
    CHECK_EQ(position.getY(), 8);
    CHECK_EQ(position.getString(), "a8");
}

TEST_CASE("Invalid position") {
    CHECK_THROWS_WITH_AS(Position("i9"),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position("`0"),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position("a9"),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position("i1"),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position("`1"),
                         "Invalid position.",
                         std::invalid_argument);
    CHECK_THROWS_WITH_AS(Position("a0"),
                         "Invalid position.",
                         std::invalid_argument);
}

TEST_CASE("Compare positions") {
    CHECK_EQ(Position(1, 1), Position("a1"));
    CHECK_EQ(Position(8, 8), Position("h8"));
    CHECK_EQ(Position(4, 5), Position("d5"));

    CHECK_NE(Position(1, 1), Position("a2"));
    CHECK_NE(Position(1, 1), Position("b1"));
    CHECK_NE(Position(1, 1), Position("b2"));
    CHECK_NE(Position(1, 2), Position("b1"));
}
}
