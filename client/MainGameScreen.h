//
// Created by ale on 20/11/21.
//

#ifndef QUANTUM_CHESS_MAINGAMESCREEN_H
#define QUANTUM_CHESS_MAINGAMESCREEN_H

struct PersistentInputData {
    bool chatClicked;
    std::string message;
    char typeOfMove;
    bool pieceSelected;
    bool firstEmptySelected;
    int positionFromX;
    int positionFromY;
    int secondPositionX;
    int secondPositionY;
};

#include <unordered_map>
#include "BlockingQueue.h"
#include "ChatUI.h"

struct Colors {
    SDL_Color normalMove;
    SDL_Color splitMove;
    SDL_Color mergeMove;
    SDL_Color grey;
    SDL_Color darkRed;
    SDL_Color darkGreen;
};
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
    //std::unique_ptr<SDL2pp::SDL> sdl;
    //std::thread myThread;
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    std::unordered_map<char,SDL2pp::Texture> selectedTexturesMap;
    std::unique_ptr<SDL2pp::Texture> moveNotificationTexture;
    std::list<Piece*> selectedPieces;
    Board &_board;
    //Client *_client;
    //std::vector<Button> buttons;
    BlockingQueue<std::shared_ptr<Message>>* userInputQueue;
    const int boardWidth = 640;
    const int chatWidth = 300;
    const int screenWidth = boardWidth + chatWidth;
    const int screenHeight = 480;
    const int pieceWidth = boardWidth / 8;
    const int pieceHeight = screenHeight / 8;
    const int selectedPieceWidth = boardWidth / 7;
    const int selectedPieceHeight = screenHeight / 7;
    const float probabilityBarWidthMultiplier = .9;
    const float probabilityBarHeightMultiplier = .14;
    PersistentInputData inputData;
    Colors colors;
    std::unique_ptr<ChatUI> chatUI;
public:
    MainGameScreen(Board& board, BlockingQueue<std::shared_ptr<Message>>* userInputQueue);
    void refreshScreen();

    void processUserInput(bool& gameFinished);

    void selectPiece(int x, int y, const SDL_Color& color);

    void deselectAllPieces();

    void handleMouseClick();

    void paintMoveSelectedNotification(const SDL_Color& color);

    //SDL2pp::Renderer createRenderer();
    void initColors();

    void goToDefaultMovement();

    void loadMoveSelectedNotification(const int alpha);

    void loadBoardTextures();

    void setUserInputDefaultValues();

    void startSDLWindow();

    void renderProbabilityBar(const int x,
                              const int y,
                              const int width,
                              const int height,
                              float percent,
                              const SDL_Color frontColor,
                              const SDL_Color backgroundColor,
                              const SDL_Color edgeColor);

    void handleBoardClick();

    void handleChatClick(int mouseX, int mouseY);

    void manageBoardEvent(SDL_Event &event, bool& gameFinished);

    void manageChatEvent(SDL_Event &event, bool& gameFinished);

    void whereDidMouseClicked();
};


#endif //QUANTUM_CHESS_MAINGAMESCREEN_H
