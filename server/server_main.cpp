#include <cstdio>
#include <iostream>
#include <vector>

#include "Board.h"
#include "RoomManager.h"

int main() {
    printf("STARTING SERVER\n");
    Board board;

    /*Piece* piece = *board.begin();
    Position position = piece->getPossibleMoves().front();
    piece->move(position);*/
    /*board.move(Position(1,2), Position(1,4));
    board.printBoard();*/

    RoomManager roomManager;
    roomManager.start();
    return 0;
}
