#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "tests/doctest/doctest.h"
#include "common/chess_game/Board.h"

TEST_SUITE("Blocking Queue Tests") {
TEST_CASE("Create Chess Board") {
    Board board;
    for(Piece piece : board){
        CHECK_EQ(1, 1);
    }
}
}
