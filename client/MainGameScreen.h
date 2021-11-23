//
// Created by ale on 20/11/21.
//

#ifndef QUANTUM_CHESS_MAINGAMESCREEN_H
#define QUANTUM_CHESS_MAINGAMESCREEN_H


#include <Board.h>
#include <unordered_map>
#include "Screen.h"
#include "Client.h"

#define BOARD_KEY 'Z'

#define WHITE_PAWN_KEY 'P'
#define WHITE_ROOK_KEY 'R'
#define WHITE_KNIGHT_KEY 'N'
#define WHITE_BISHOP_KEY 'B'
#define WHITE_KING_KEY 'K'
#define WHITE_QUEEN_KEY 'Q'

#define BLACK_PAWN_KEY 'p'
#define BLACK_ROOK_KEY 'r'
#define BLACK_KNIGHT_KEY 'n'
#define BLACK_BISHOP_KEY 'b'
#define BLACK_KING_KEY 'k'
#define BLACK_QUEEN_KEY 'q'


#define BOARD_FILEPATH "../assets/sprites/board.png"

#define WHITE_PAWN_FILEPATH "../assets/sprites/whitePawn.png"
#define WHITE_ROOK_FILEPATH "../assets/sprites/whiteRook.png"
#define WHITE_KNIGHT_FILEPATH "../assets/sprites/whiteKnight.png"
#define WHITE_BISHOP_FILEPATH "../assets/sprites/whiteBishop.png"
#define WHITE_KING_FILEPATH "../assets/sprites/whiteKing.png"
#define WHITE_QUEEN_FILEPATH "../assets/sprites/whiteQueen.png"

#define BLACK_PAWN_FILEPATH "../assets/sprites/blackPawn.png"
#define BLACK_ROOK_FILEPATH "../assets/sprites/blackRook.png"
#define BLACK_KNIGHT_FILEPATH "../assets/sprites/blackKnight.png"
#define BLACK_BISHOP_FILEPATH "../assets/sprites/blackBishop.png"
#define BLACK_KING_FILEPATH "../assets/sprites/blackKing.png"
#define BLACK_QUEEN_FILEPATH "../assets/sprites/blackQueen.png"

class MainGameScreen : public Screen {
private:
    std::thread myThread;
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    Board *_board;
    //Client *_client;
    std::vector<Button> buttons;
    BlockingQueue<std::shared_ptr<Message>>* userInputQueue;
    int screenWidth = 640;
    int screenHeight = 480;
    int pieceWidth = screenWidth / 8;
    int pieceHeight = screenHeight / 8;
public:
    MainGameScreen(SDL2pp::Renderer &renderer, Board* board, BlockingQueue<std::shared_ptr<Message>>* userInputQueue);
    int start() override;
    void redraw() override;

    void run();

    void join();
};


#endif //QUANTUM_CHESS_MAINGAMESCREEN_H
