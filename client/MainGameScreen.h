//
// Created by ale on 20/11/21.
//

#ifndef QUANTUM_CHESS_MAINGAMESCREEN_H
#define QUANTUM_CHESS_MAINGAMESCREEN_H


#include <Board.h>
#include <unordered_map>
#include "Screen.h"

#define BOARD_KEY 'Z'
#define PAWN_KEY 'P'
#define ROOK_KEY 'R'
#define KNIGHT_KEY 'N'
#define BISHOP_KEY 'B'
#define KING_KEY 'K'
#define QUEEN_KEY 'Q'


#define BOARD_FILEPATH "../assets/sprites/board.png"
#define PAWN_FILEPATH "../assets/sprites/pawn.png"
#define ROOK_FILEPATH "../assets/sprites/rook.png"
#define KNIGHT_FILEPATH "../assets/sprites/knight.png"
#define BISHOP_FILEPATH "../assets/sprites/bishop.png"
#define KING_FILEPATH "../assets/sprites/king.png"
#define QUEEN_FILEPATH "../assets/sprites/queen.png"

class MainGameScreen : public Screen {
private:
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    Board *_board;
public:
    MainGameScreen(SDL2pp::Renderer &renderer, Board* board);
    int start() override;
    void redraw() override;

};


#endif //QUANTUM_CHESS_MAINGAMESCREEN_H
