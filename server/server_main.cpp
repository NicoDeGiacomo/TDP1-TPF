#include <cstdio>
#include <iostream>
#include <vector>

#include "common/chess_game/Board.h"
#include "common/Socket.h"

void start_socket_and_receive_2_bytes_to_test();

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
    return 0;
}