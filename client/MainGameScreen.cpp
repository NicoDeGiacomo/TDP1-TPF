//
// Created by ale on 20/11/21.
//

//#include <SDL_image.h>
#include <NormalMove.h>
#include <NormalMoveMessage.h>
#include <thread>
#include <SplitMoveMessage.h>
#include <MergeMoveMessage.h>
#include "Button.h"
#include "MainGameScreen.h"
#include "EventManager.h"

MainGameScreen::MainGameScreen(SDL2pp::Renderer &renderer, Board* board, BlockingQueue<std::shared_ptr<Message>>* queue) : Screen(renderer) {
    this->userInputQueue = queue;
    this->_board = board;
    texturesMap.insert({BOARD_KEY, SDL2pp::Texture(renderer, BOARD_FILEPATH)});

    texturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture(renderer, WHITE_PAWN_FILEPATH)});
    texturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture(renderer, WHITE_ROOK_FILEPATH)});
    texturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture(renderer, WHITE_KNIGHT_FILEPATH)});
    texturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture(renderer, WHITE_BISHOP_FILEPATH)});
    texturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture(renderer, WHITE_KING_FILEPATH)});
    texturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture(renderer, WHITE_QUEEN_FILEPATH)});

    texturesMap.insert({BLACK_PAWN_KEY, SDL2pp::Texture(renderer, BLACK_PAWN_FILEPATH)});
    texturesMap.insert({BLACK_ROOK_KEY, SDL2pp::Texture(renderer, BLACK_ROOK_FILEPATH)});
    texturesMap.insert({BLACK_KNIGHT_KEY, SDL2pp::Texture(renderer, BLACK_KNIGHT_FILEPATH)});
    texturesMap.insert({BLACK_BISHOP_KEY, SDL2pp::Texture(renderer, BLACK_BISHOP_FILEPATH)});
    texturesMap.insert({BLACK_KING_KEY, SDL2pp::Texture(renderer, BLACK_KING_FILEPATH)});
    texturesMap.insert({BLACK_QUEEN_KEY, SDL2pp::Texture(renderer, BLACK_QUEEN_FILEPATH)});
    //renderer.Copy(texturesMap.at(PAWN_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);
    //std::string asd = "BUTTON";
    //Button button(renderer, asd, 30, 50, 50, A_CENTER);
    //button.onClick([](){ EventManager::OnStartGamePressed(); });
    //this->buttons.push_back(button);
    redraw();
}

void MainGameScreen::run() {
    SDL_bool done = SDL_FALSE;
    bool pieceSelected = false;
    bool firstEmptySelected = false;
    char typeOfMove = 'n';

    while (!done) {

        // Event processing:
        // - If window is closed, or Q or Escape buttons are pressed,
        //   quit the application
        SDL_Event event;
        int positionFromX;
        int positionFromY;
        int positionFrom2X;
        int positionFrom2Y;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: case SDLK_q:
                            return;
                        case SDLK_n:
                            std::cout << "NNNNNNNNNNNNNNNNNN" << std::endl;
                            typeOfMove = 'n';
                            break;
                        case SDLK_s:
                            std::cout << "SSSSSSSSSSSSSSSSSSSSSSSSS" << std::endl;
                            typeOfMove = 's';
                            break;
                        case SDLK_m:
                            std::cout << "MMMMMMMMMMMMMMMMMMMMM" << std::endl;
                            typeOfMove = 'm';
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "xmouse " << mouseX << " ymouse " << mouseY << std::endl;
                    int clampedMouseXToGrid = ceil((float)mouseX / pieceWidth);
                    int clampedMouseYToGrid = ceil((float)mouseY / pieceHeight);
                    std::cout << "grid position x " << clampedMouseXToGrid << " grid position y " << clampedMouseYToGrid << std::endl;
                    switch (typeOfMove) {
                        case 'n':
                            if (pieceSelected) {
                                /*this->userInputQueue->produce(std::make_shared<NormalMoveMessage>(
                                        Position(positionFromX, positionFromY),
                                        Position(clampedMouseXToGrid, clampedMouseYToGrid)));*/
                                //todo: remove this, mega hardcoded
                                std::string message = "n";
                                message += std::to_string(positionFromX) +
                                           std::to_string(positionFromY) +
                                           std::to_string(clampedMouseXToGrid) +
                                           std::to_string(clampedMouseYToGrid);
                                std::cout << "message hardcoded is: " << message << std::endl;
                                this->userInputQueue->produce(std::make_shared<NormalMoveMessage>(
                                        message, 2
                                ));
                                //todo: elegir entre esto v o esto ^
                                /*cliente.movePieza(Position1, position2)
                                    //cliente mueve en su board,
                                    //cliente envia el movimiento al sv*/
                            }
                            else {
                                positionFromX = clampedMouseXToGrid;
                                positionFromY = clampedMouseYToGrid;
                            }
                            pieceSelected = !pieceSelected;
                            break;
                        case 's':
                            std::cout << "enter split" << std::endl;
                            if (!pieceSelected){
                                positionFromX = clampedMouseXToGrid;
                                positionFromY = clampedMouseYToGrid;
                                pieceSelected = true;
                                firstEmptySelected = false;
                            } else if (!firstEmptySelected) {
                                positionFrom2X = clampedMouseXToGrid;
                                positionFrom2Y = clampedMouseYToGrid;
                                firstEmptySelected = true;
                            } else {
                                std::string message = "s";
                                message += std::to_string(positionFromX) +
                                           std::to_string(positionFromY) +
                                            std::to_string(positionFrom2X) +
                                            std::to_string(positionFrom2Y) +
                                           std::to_string(clampedMouseXToGrid) +
                                           std::to_string(clampedMouseYToGrid);
                                std::cout << "message hardcoded is: " << message << std::endl;
                                this->userInputQueue->produce(std::make_shared<SplitMoveMessage>(
                                        message, 2
                                ));
                                pieceSelected = false;
                                firstEmptySelected = false;
                                typeOfMove = 'n';
                            }
                            break;
                        case 'm':
                            std::cout << "enter merge" << std::endl;
                            if (!pieceSelected){
                                positionFromX = clampedMouseXToGrid;
                                positionFromY = clampedMouseYToGrid;
                                pieceSelected = true;
                                firstEmptySelected = false;
                            } else if (!firstEmptySelected) {
                                positionFrom2X = clampedMouseXToGrid;
                                positionFrom2Y = clampedMouseYToGrid;
                                firstEmptySelected = true;
                            } else {
                                std::string message = "m";
                                message += std::to_string(positionFromX) +
                                           std::to_string(positionFromY) +
                                           std::to_string(positionFrom2X) +
                                           std::to_string(positionFrom2Y) +
                                           std::to_string(clampedMouseXToGrid) +
                                           std::to_string(clampedMouseYToGrid);
                                std::cout << "message hardcoded is: " << message << std::endl;
                                this->userInputQueue->produce(std::make_shared<MergeMoveMessage>(
                                        message, 2
                                ));
                                pieceSelected = false;
                                firstEmptySelected = false;
                                typeOfMove = 'n';
                            }
                        default:
                            break;
                    }
            }
        }

        redraw();

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        SDL_Delay(1);
    }
}
int MainGameScreen::start() {
    this->myThread = std::thread(&MainGameScreen::run, this);
    return 0;
}

void MainGameScreen::join() {
    this->myThread.join();
}

void MainGameScreen::redraw() {
    //todo: this shouldn't be hardcoded, also make 'redraw()' listen for screen resize
    // Clear screen
    renderer.Clear();

    renderer.Copy(texturesMap.at(BOARD_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);

    //this->buttons.front().redraw();

    for (const auto &piece : (*_board)) {
        piece->getDrawing();
        SDL2pp::Rect pieceRect(
                (piece->getPosition().getX() - 1)* pieceWidth,
                 (piece->getPosition().getY() - 1) * pieceHeight,
                pieceWidth,
                pieceHeight);
        renderer.Copy(texturesMap.at(piece->getDrawing()), SDL2pp::NullOpt, pieceRect);
    }

    // Show rendered frame
    renderer.Present();
}
