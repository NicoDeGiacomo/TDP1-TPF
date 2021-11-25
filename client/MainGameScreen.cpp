//
// Created by ale on 20/11/21.
//

//#include <SDL_image.h>
#include <NormalMove.h>
#include <NormalMoveMessage.h>
#include <thread>
#include <SplitMoveMessage.h>
#include <MergeMoveMessage.h>
#include "MainGameScreen.h"
#include "EventManager.h"

MainGameScreen::MainGameScreen(Board& board, BlockingQueue<std::shared_ptr<Message>>* queue) : _board(board) {
    sdl = std::make_unique<SDL2pp::SDL>((SDL_INIT_VIDEO | SDL_INIT_AUDIO));
    window = std::make_unique<SDL2pp::Window>("Quantum Chess",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     640,
                                     480,
                                     SDL_WINDOW_RESIZABLE);
    renderer = std::make_unique<SDL2pp::Renderer>((*window), -1, SDL_RENDERER_ACCELERATED);

    pieceSelected = false;
    firstEmptySelected = false;
    typeOfMove = 'n';
    positionFromX = 0;
    positionFromY = 0;
    secondPositionX = 0;
    secondPositionY = 0;
    this->userInputQueue = queue;
    texturesMap.insert({BOARD_KEY, SDL2pp::Texture((*renderer), BOARD_FILEPATH)});

    texturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*renderer), WHITE_PAWN_FILEPATH)});
    texturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*renderer), WHITE_ROOK_FILEPATH)});
    texturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*renderer), WHITE_KNIGHT_FILEPATH)});
    texturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*renderer), WHITE_BISHOP_FILEPATH)});
    texturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*renderer), WHITE_KING_FILEPATH)});
    texturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*renderer), WHITE_QUEEN_FILEPATH)});

    texturesMap.insert({BLACK_PAWN_KEY, SDL2pp::Texture((*renderer), BLACK_PAWN_FILEPATH)});
    texturesMap.insert({BLACK_ROOK_KEY, SDL2pp::Texture((*renderer), BLACK_ROOK_FILEPATH)});
    texturesMap.insert({BLACK_KNIGHT_KEY, SDL2pp::Texture((*renderer), BLACK_KNIGHT_FILEPATH)});
    texturesMap.insert({BLACK_BISHOP_KEY, SDL2pp::Texture((*renderer), BLACK_BISHOP_FILEPATH)});
    texturesMap.insert({BLACK_KING_KEY, SDL2pp::Texture((*renderer), BLACK_KING_FILEPATH)});
    texturesMap.insert({BLACK_QUEEN_KEY, SDL2pp::Texture((*renderer), BLACK_QUEEN_FILEPATH)});

    selectedTexturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*renderer), SELECTED_PAWN_FILEPATH)});
    selectedTexturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*renderer), SELECTED_ROOK_FILEPATH)});
    selectedTexturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*renderer), SELECTED_KNIGHT_FILEPATH)});
    selectedTexturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*renderer), SELECTED_BISHOP_FILEPATH)});
    selectedTexturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*renderer), SELECTED_KING_FILEPATH)});
    selectedTexturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*renderer), SELECTED_QUEEN_FILEPATH)});
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font, 12pt size
    SDL2pp::Font font("../assets/fonts/Vera.ttf", this->selectedPieceHeight * 2);

    // Render the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    moveNotifText = std::make_unique<SDL2pp::Texture>(
            (*renderer),
            font.RenderText_Blended("*", SDL_Color{255, 255, 255, 255}));//default normal move color
    showMoveSelectedNotif(Uint8(250), Uint8(15), Uint8(180));
    refresh();
}

void MainGameScreen::processUserInput(bool& gameFinished) {
    // Event processing:
    // - If window is closed, or Q or Escape buttons are pressed,
    //   quit the application
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: case SDLK_q:
                        gameFinished = true;
                        return;
                    case SDLK_n:
                        std::cout << "NNNNNNNNNNNNNNNNNN" << std::endl;
                        typeOfMove = 'n';
                        //normal move selection color
                        showMoveSelectedNotif(Uint8(250), Uint8(15), Uint8(188));
                        break;
                    case SDLK_s:
                        std::cout << "SSSSSSSSSSSSSSSSSSSSSSSSS" << std::endl;
                        typeOfMove = 's';
                        //split move selection color
                        showMoveSelectedNotif(Uint8(0), Uint8(255), Uint8(255));
                        break;
                    case SDLK_m:
                        std::cout << "MMMMMMMMMMMMMMMMMMMMM" << std::endl;
                        typeOfMove = 'm';
                        //merge move selection color
                        showMoveSelectedNotif(Uint8(0), Uint8(128), Uint8(0));
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick();
        }
    }
}
/*int MainGameScreen::start() {
    this->myThread = std::thread(&MainGameScreen::run, this);
    return 0;
}

void MainGameScreen::join() {
    this->myThread.join();
}*/

void MainGameScreen::refresh() {
    //todo: this shouldn't be hardcoded, also make 'redraw()' listen for screen resize
    // Clear screen
    renderer->Clear();

    renderer->Copy(texturesMap.at(BOARD_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);

    //this->buttons.front().redraw();
    for (auto &piece : selectedPieces) {
        SDL2pp::Rect pieceRect(
                (piece->getPosition().getX() - 1) * pieceWidth + (pieceWidth - selectedPieceWidth)/2,
                (piece->getPosition().getY() - 1) * pieceHeight + (pieceHeight - selectedPieceHeight)/2,
                selectedPieceWidth,
                selectedPieceHeight);
        renderer->Copy(selectedTexturesMap.at(toupper(piece->getDrawing())), SDL2pp::NullOpt, pieceRect);
    }

    for (const auto &piece : _board) {
        SDL2pp::Rect pieceRect(
                (piece->getPosition().getX() - 1) * pieceWidth,
                (piece->getPosition().getY() - 1) * pieceHeight,
                pieceWidth,
                pieceHeight);
        renderer->Copy(texturesMap.at(piece->getDrawing()), SDL2pp::NullOpt, pieceRect);
    }

    //show move notif
    SDL2pp::Rect textNotifRect(
            0,
            -moveNotifText->GetHeight()/8,
            moveNotifText->GetWidth(),
            moveNotifText->GetHeight()
            );
    renderer->Copy((*moveNotifText), SDL2pp::NullOpt, textNotifRect);


    // Show rendered frame
    renderer->Present();
}

void MainGameScreen::selectPiece(int x, int y, const Uint8& r, const Uint8& g, const Uint8& b) {
    Piece* piece = _board.getPiece(Position(x,y));
    if (!piece)
        return;
    selectedPieces.push_front(piece);
    SDL2pp::Texture &texture = selectedTexturesMap.at(toupper(piece->getDrawing()));
    SDL_SetTextureAlphaMod(texture.Get(), Uint8(127));
    SDL_SetTextureColorMod(texture.Get(), r, g, b);
}

void MainGameScreen::deselectAllPieces() {
    selectedPieces.clear();
}

void MainGameScreen::handleMouseClick() {
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
                std::string message;
                message += std::to_string(positionFromX) +
                           std::to_string(positionFromY) +
                           std::to_string(clampedMouseXToGrid) +
                           std::to_string(clampedMouseYToGrid);
                std::cout << "message hardcoded is: " << message << std::endl;
                this->userInputQueue->produce(std::make_shared<NormalMoveMessage>(
                        message, 2
                ));
                deselectAllPieces();
            }
            else {
                positionFromX = clampedMouseXToGrid;
                positionFromY = clampedMouseYToGrid;
                selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, Uint8(250), Uint8(15), Uint8(188));
                // pintar pieza seleccionada
                // NTH: pintar movimientos posibles
            }
            pieceSelected = !pieceSelected;
            break;
        case 's':
        case 'm':
            if (!pieceSelected){
                positionFromX = clampedMouseXToGrid;
                positionFromY = clampedMouseYToGrid;
                pieceSelected = true;
                firstEmptySelected = false;
                Uint8 r = 0, g = 128, b = 0;
                if (typeOfMove == 's') {
                    r = 0;
                    g = 255;
                    b = 255;
                }

                selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, r, g, b);
            } else if (!firstEmptySelected) {
                secondPositionX = clampedMouseXToGrid;
                secondPositionY = clampedMouseYToGrid;
                firstEmptySelected = true;
                if (typeOfMove == 'm')
                    selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, Uint8(0), Uint8(128), Uint8(0));
            } else {
                std::string message;
                message += std::to_string(positionFromX) +
                           std::to_string(positionFromY) +
                           std::to_string(secondPositionX) +
                           std::to_string(secondPositionY) +
                           std::to_string(clampedMouseXToGrid) +
                           std::to_string(clampedMouseYToGrid);
                std::cout << "message hardcoded is: " << message << std::endl;

                if (typeOfMove == 's')
                    this->userInputQueue->produce(std::make_shared<SplitMoveMessage>(message, 2));
                else
                    this->userInputQueue->produce(std::make_shared<MergeMoveMessage>(message, 2));
                pieceSelected = false;
                firstEmptySelected = false;
                typeOfMove = 'n';
                deselectAllPieces();
            }
        default:
            break;
    }
}

void MainGameScreen::showMoveSelectedNotif(const Uint8& r, const Uint8& g, const Uint8& b) {
    SDL_SetTextureAlphaMod(moveNotifText->Get(), Uint8(233));
    SDL_SetTextureColorMod(moveNotifText->Get(), r, g, b);
}
