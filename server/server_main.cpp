#include <cstdio>

#include "common/chess_game/Board.h"

void print_board(Board &board) {
    char chessBoard[8][8]{};
    for (const auto& piece : board) {
        chessBoard[piece.getPosition().getY()-1][piece.getPosition().getX()-1] = piece.getDrawing();
    }

    for (auto & file : chessBoard) {
        //printf("--------\n");
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
    //printf("--------\n");

}

int main() {
    printf("STARTING SERVER\n");
    Board board;

    board.begin()->move(Position(4, 4));

    print_board(board);

    return 0;
}
