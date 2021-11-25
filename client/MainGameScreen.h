//
// Created by ale on 20/11/21.
//

#ifndef QUANTUM_CHESS_MAINGAMESCREEN_H
#define QUANTUM_CHESS_MAINGAMESCREEN_H

struct PersistentInputData {
    char typeOfMove;
    bool pieceSelected;
    bool firstEmptySelected;
    int positionFromX;
    int positionFromY;
    int secondPositionX;
    int secondPositionY;
};

#include <unordered_map>
#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "BlockingQueue.h"

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

#define SELECTED_PAWN_FILEPATH "../assets/sprites/selectedPawn.png"
#define SELECTED_ROOK_FILEPATH "../assets/sprites/selectedRook.png"
#define SELECTED_KNIGHT_FILEPATH "../assets/sprites/selectedKnight.png"
#define SELECTED_BISHOP_FILEPATH "../assets/sprites/selectedBishop.png"
#define SELECTED_KING_FILEPATH "../assets/sprites/selectedKing.png"
#define SELECTED_QUEEN_FILEPATH "../assets/sprites/selectedQueen.png"

class MainGameScreen {
private:
    std::unique_ptr<SDL2pp::Renderer> renderer;
    std::unique_ptr<SDL2pp::Window> window;
    std::unique_ptr<SDL2pp::SDL> sdl;
    //std::thread myThread;
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    std::unordered_map<char,SDL2pp::Texture> selectedTexturesMap;
    std::unique_ptr<SDL2pp::Texture> moveNotifText;
    std::list<Piece*> selectedPieces;
    Board &_board;
    //Client *_client;
    //std::vector<Button> buttons;
    BlockingQueue<std::shared_ptr<Message>>* userInputQueue;
    int screenWidth = 640;
    int screenHeight = 480;
    int pieceWidth = screenWidth / 8;
    int pieceHeight = screenHeight / 8;
    int selectedPieceWidth = screenWidth / 7;
    int selectedPieceHeight = screenHeight / 7;
    PersistentInputData inputData;
public:
    MainGameScreen(Board& board, BlockingQueue<std::shared_ptr<Message>>* userInputQueue);
    int start();
    void refresh();

    void processUserInput(bool& gameFinished);

    void join();

    void selectPiece(int x, int y, const Uint8& r, const Uint8& g, const Uint8& b);

    void deselectAllPieces();

    void handleMouseClick();

    void showMoveSelectedNotif(const Uint8& r, const Uint8& g, const Uint8& b);

    //SDL2pp::Renderer createRenderer();
};


#endif //QUANTUM_CHESS_MAINGAMESCREEN_H
