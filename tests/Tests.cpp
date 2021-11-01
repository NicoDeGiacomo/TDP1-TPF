#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "tests/doctest/doctest.h"  // NOLINT [build/c++11]

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <list>  // NOLINT [build/c++11]
#include <algorithm>  // NOLINT [build/c++11]
#include <stdexcept>  // NOLINT [build/c++11]
#include <vector>  // NOLINT [build/c++11]
#include <iostream>  // NOLINT [build/c++11]
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "Position.h"
#include "Board.h"

static bool findPosition_(const std::list<Position>& positions,
                          Position position) {
    return std::find(positions.begin(), positions.end(), position)
        != positions.end();
}

static int countPieces_(const Board& board) {
    return (int) std::distance(board.begin(), board.end());
}

TEST_SUITE("Initial") {
TEST_CASE("findPosition_") {
    std::list<Position> positions;
    positions.emplace_back(1, 1);
    CHECK(findPosition_(positions, Position(1, 1)));
}

TEST_CASE("countPieces_") {
    Board board;
    CHECK_EQ(32, countPieces_(board));
}
}
