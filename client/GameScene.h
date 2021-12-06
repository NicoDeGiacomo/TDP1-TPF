#ifndef QUANTUM_CHESS_GAMESCENE_H
#define QUANTUM_CHESS_GAMESCENE_H

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
#include "Protocol.h"
#include "ChatUI.h"
#include "Scene.h"

struct Colors {
    SDL_Color normalMove;
    SDL_Color splitMove;
    SDL_Color mergeMove;
    SDL_Color grey;
    SDL_Color darkRed;
    SDL_Color darkGreen;
    SDL_Color entangled;
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
#define DOT_FILEPATH "../assets/sprites/dot.png"

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

class GameScene : public Scene {
private:
    //std::unique_ptr<SDL2pp::Renderer> _renderer;
    std::unique_ptr<SDL2pp::Window> window;
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    std::unordered_map<char,SDL2pp::Texture> selectedTexturesMap;
    std::unordered_map<char,SDL2pp::Texture> entangledTexturesMap;
    std::unique_ptr<SDL2pp::Texture> moveNotificationTexture;
    std::unique_ptr<SDL2pp::Texture> dotTexture;
    std::list<Piece*> selectedPieces;
    std::list<Position> possibleMoves;
    std::list<Position> entangledPiecesPosition;
    Board &_board;
    BlockingQueue<std::shared_ptr<Message>>* userInputQueue;
    const int boardWidth = 480;
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
    char _playerType;
    bool& _gameFinished;

    void render() override;
    void handleEvents() override;
public:
    GameScene(Board& board,
              BlockingQueue<std::shared_ptr<Message>>* userInputQueue,
              BlockingQueue<std::shared_ptr<std::string>> &chatQueue,
              char playerType, bool& gameFinished);

    void refreshScreen();

    void processUserInput();

    void selectPiece(const int x, const int y, const SDL_Color& color, bool merge = false);

    void deselectAllPieces();

    void paintMoveSelectedNotification(const SDL_Color& color);

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

    void manageBoardEvent(SDL_Event &event);

    void manageChatEvent(SDL_Event &event);

    void whereDidMouseClicked();

    void loadPossibleMoves(const Piece* piece, const SDL_Color& color, bool merge = false);

    void endMessage(char endstate);

    void showEntangledPieces(Piece *piece);

    bool canMovePiece();

    //std::string login();
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer) override;
};


#endif //QUANTUM_CHESS_GAMESCENE_H
