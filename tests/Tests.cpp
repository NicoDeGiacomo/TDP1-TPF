#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "tests/doctest/doctest.h"

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <list>
#include <algorithm>
#include <stdexcept>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

#include "Position.h"

static bool findPosition_(std::list<Position> &positions, Position position) {
    return std::find(positions.begin(), positions.end(), position)
        != positions.end();
}

TEST_SUITE("Initial") {
TEST_CASE("findPosition_") {
    std::list<Position> positions;
    positions.emplace_back(1, 1);
    CHECK(findPosition_(positions, Position(1, 1)));
}
}
