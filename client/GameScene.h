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
    SDL_Color entangled;
    SDL_Color samePiece;
    SDL_Color grey;
    SDL_Color darkRed;
    SDL_Color darkGreen;
    SDL_Color white;
    SDL_Color black;
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


#define BOARD_PNG "assets/sprites/board.png"
#define DOT_PNG "assets/sprites/dot.png"

#define WHITE_PAWN_PNG "assets/sprites/whitePawn.png"
#define WHITE_ROOK_PNG "assets/sprites/whiteRook.png"
#define WHITE_KNIGHT_PNG "assets/sprites/whiteKnight.png"
#define WHITE_BISHOP_PNG "assets/sprites/whiteBishop.png"
#define WHITE_KING_PNG "assets/sprites/whiteKing.png"
#define WHITE_QUEEN_PNG "assets/sprites/whiteQueen.png"

#define BLACK_PAWN_PNG "assets/sprites/blackPawn.png"
#define BLACK_ROOK_PNG "assets/sprites/blackRook.png"
#define BLACK_KNIGHT_PNG "assets/sprites/blackKnight.png"
#define BLACK_BISHOP_PNG "assets/sprites/blackBishop.png"
#define BLACK_KING_PNG "assets/sprites/blackKing.png"
#define BLACK_QUEEN_PNG "assets/sprites/blackQueen.png"

#define SELECTED_PAWN_PNG "assets/sprites/selectedPawn.png"
#define SELECTED_ROOK_PNG "assets/sprites/selectedRook.png"
#define SELECTED_KNIGHT_PNG "assets/sprites/selectedKnight.png"
#define SELECTED_BISHOP_PNG "assets/sprites/selectedBishop.png"
#define SELECTED_KING_PNG "assets/sprites/selectedKing.png"
#define SELECTED_QUEEN_PNG "assets/sprites/selectedQueen.png"

#define BOARD_SQUARES_IN_A_LINE 8
#define PROBABILITY_BAR_WIDTH_MULTIPLIER .9f
#define PROBABILITY_BAR_HEIGHT_MULTIPLIER .14f

class GameScene : public Scene {
private:
    std::unordered_map<char,SDL2pp::Texture> texturesMap;
    std::unordered_map<char,SDL2pp::Texture> selectedTexturesMap;
    std::unordered_map<char,SDL2pp::Texture> entangledTexturesMap;
    std::unordered_map<char,SDL2pp::Texture> samePieceSplitTextureMap;
    std::unique_ptr<SDL2pp::Texture> moveNotificationTexture;
    std::unique_ptr<SDL2pp::Texture> turnNotificationTexture;
    std::unique_ptr<SDL2pp::Texture> dotTexture;
    std::list<Piece*> selectedPieces;
    std::list<Position> possibleMoves;
    std::list<Position> entangledPiecesPosition;
    std::list<Position> splitsOfSamePiece;
    Board &_board;
    BlockingQueue<std::shared_ptr<Message>>* userInputQueue;
    int pieceSize, selectedPieceSize;
    PersistentInputData inputData;
    Colors colors;
    std::unique_ptr<ChatUI> chatUI;
    char _playerType;
    bool& _gameFinished;
    bool mute;

    void render() override;
    void handleEvents() override;
public:
    GameScene(Board& board,
              BlockingQueue<std::shared_ptr<Message>>* userInputQueue,
              BlockingQueue<std::shared_ptr<std::string>> &chatQueue,
              char playerType, bool& gameFinished, bool mute = false);

    void selectPiece(const int x, const int y, const SDL_Color& color, bool merge = false);

    void deselectAllPieces();

    void paintMoveSelectedNotification(const SDL_Color& color);

    void initColors();

    void goToDefaultMovement();

    void loadNotifications();

    void loadBoardTextures();

    void setUserInputDefaultValues();

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
    void updateLoop() override;
    void load(SDL2pp::Renderer* renderer, SDL2pp::Window *window) override;

    void paintTurnNotification(SDL_Color &color);

    void showSamePieceSplits(Piece *piece);
};


#endif //QUANTUM_CHESS_GAMESCENE_H
