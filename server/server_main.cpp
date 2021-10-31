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

    //Piece* piece = *board.begin();
    //piece->move(piece->getPossiblePositions().front());
    // piece->move(Position(4, 4));

    print_board(board);
    start_socket_and_receive_2_bytes_to_test();

    return 0;
}

void start_socket_and_receive_2_bytes_to_test() {
    Socket socket;
    socket.bind("7777");
    socket.listen(5);
    socket = socket.accept();
    std::vector<char> buffer(3);
    buffer [0] = 0;
    buffer [1] = 0;
    socket.receive(&buffer[0], 2);
    //print buffer
    for (int i = 0; i<2 ; i++){
        std::cout << buffer[i] << std::endl;
    }
}