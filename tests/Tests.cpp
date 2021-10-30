#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "tests/doctest/doctest.h"
#include "common/chess_game/Board.h"

TEST_SUITE("Blocking Queue Tests") {
TEST_CASE("Create Chess Board") {
    Board board;

    unsigned short count = 0;
    for(Piece piece : board){
        count++;
    }
    CHECK_EQ(32, count);
}
}
