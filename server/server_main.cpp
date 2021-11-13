#include <cstdio>
#include <iostream>
#include <vector>

#include "Board.h"
#include "RoomManager.h"

void print_board(const Board &board) {
    char chessBoard[8][8]{};
    for (const auto &piece : board) {
        chessBoard[piece->getPosition().getY() - 1][piece->getPosition().getX()
            - 1] = piece->getDrawing();
    }

    for (auto &file : chessBoard) {
        // printf("--------\n");
        for (char square : file) {
            printf("|");
            if (square) {
                printf("%c", square);
            } else {
                printf(" ");
            }
        }
        printf("|");
        printf("\n");
    }
    // printf("--------\n");
}

int main() {
    printf("STARTING SERVER\n");
    Board board;

    Piece* piece = *board.begin();
    Position position = piece->getPossibleMoves().front();
    piece->move(position);

    print_board(board);

    //TODO: encapsulate chat in room
    RoomManager chat;
    chat.start();
    return 0;
}
