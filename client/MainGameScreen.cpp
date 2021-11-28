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

MainGameScreen::MainGameScreen(Board& board, BlockingQueue<std::shared_ptr<Message>>* queue) : _board(board) {
    this->startSDLWindow();
    this->userInputQueue = queue;
    this->setUserInputDefaultValues();
    this->loadBoardTextures();
    this->initColors();
    this->loadMoveSelectedNotification(222);
    this->paintMoveSelectedNotification(colors.normalMove);
    this->refreshScreen();
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
                        std::cout << "GAME FINISHED" << std::endl;
                        gameFinished = true;
                        return;
                    case SDLK_n:
                        std::cout << "NNNNNNNNNNNNNNNNNN" << std::endl;
                        inputData.typeOfMove = 'n';
                        //normalMove move selection color
                        paintMoveSelectedNotification(colors.normalMove);
                        break;
                    case SDLK_s:
                        std::cout << "SSSSSSSSSSSSSSSSSSSSSSSSS" << std::endl;
                        inputData.typeOfMove = 's';
                        //split move selection color
                        paintMoveSelectedNotification(colors.splitMove);
                        break;
                    case SDLK_m:
                        std::cout << "MMMMMMMMMMMMMMMMMMMMM" << std::endl;
                        inputData.typeOfMove = 'm';
                        //merge move selection color
                        paintMoveSelectedNotification(colors.mergeMove);
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick();
        }
    }
}

void MainGameScreen::refreshScreen() {
    //todo: listen for screen resize

    //clear screen
    renderer->Clear();
    //render board
    renderer->Copy(texturesMap.at(BOARD_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);
    //render the highlight of selected pieces
    for (auto &piece : selectedPieces) {
        SDL2pp::Rect pieceRect(
                (piece->getPosition().getX() - 1) * pieceWidth + (pieceWidth - selectedPieceWidth)/2,
                (piece->getPosition().getY() - 1) * pieceHeight + (pieceHeight - selectedPieceHeight)/2,
                selectedPieceWidth,
                selectedPieceHeight);
        renderer->Copy(selectedTexturesMap.at(toupper(piece->getDrawing())), SDL2pp::NullOpt, pieceRect);
    }
    //render pieces
    for (const auto &piece : _board) {
        SDL2pp::Rect pieceRect(
                (piece->getPosition().getX() - 1) * pieceWidth,
                (piece->getPosition().getY() - 1) * pieceHeight,
                pieceWidth,
                pieceHeight);
        renderer->Copy(texturesMap.at(piece->getDrawing()), SDL2pp::NullOpt, pieceRect);
    }

    //render move notification text
    SDL2pp::Rect textNotifRect(
            0,
            -moveNotificationTexture->GetHeight() / 8, //place the '*' on the top left
            moveNotificationTexture->GetWidth(),
            moveNotificationTexture->GetHeight()
            );
    renderer->Copy((*moveNotificationTexture), SDL2pp::NullOpt, textNotifRect);

    renderProbabilityBar(200, 200, 100, 50, .75, colors.green, colors.red, colors.grey);
    //show rendered frame
    renderer->Present();
}
void MainGameScreen::renderProbabilityBar(const int x,
                                          const int y,
                                          const int width,
                                          const int height,
                                          float percent,
                                          const SDL_Color frontColor,
                                          const SDL_Color backgroundColor,
                                          const SDL_Color edgeColor) {
    //check if percent is valid, between 0 and 1
    percent = percent > 1.f ? 1.f : percent < 0.f ? 0.f : percent;
    int edgeSize = height / 8;
    int frontWidth = (int)((float)(width - edgeSize * 2) * percent);
    SDL2pp::Rect backgroundRect(x, y, width, height);
    SDL2pp::Rect frontRect(x + edgeSize, y, frontWidth, height);
    SDL2pp::Rect topEdge(x, y, width, edgeSize);
    SDL2pp::Rect bottomEdge(x, y + height, width, edgeSize);
    SDL2pp::Rect rightEdge(x + width - edgeSize, y, edgeSize, height);
    SDL2pp::Rect leftEdge(x, y, edgeSize, height);
    //blend mode so can overlap pixel colors based on alpha value
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer->SetDrawColor(backgroundColor);
    renderer->FillRect(backgroundRect);
    renderer->SetDrawColor(frontColor);
    renderer->FillRect(frontRect);
    //edges
    renderer->SetDrawColor(edgeColor);
    renderer->FillRect(topEdge);
    renderer->FillRect(bottomEdge);
    renderer->FillRect(rightEdge);
    renderer->FillRect(leftEdge);
    //back to none blend mode
    renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE);
}

void MainGameScreen::selectPiece(int x, int y, const SDL_Color& color) {
    Piece* piece = _board.getPiece(Position(x,y));
    if (!piece)
        return;
    selectedPieces.push_front(piece);
    SDL2pp::Texture &texture = selectedTexturesMap.at(toupper(piece->getDrawing()));
    // change opacity of selected piece highlight, leaving at 100% if line is commented
    SDL_SetTextureAlphaMod(texture.Get(), color.a);
    SDL_SetTextureColorMod(texture.Get(), color.r, color.g, color.b);
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
    switch (inputData.typeOfMove) {
        case 'n':
            if (inputData.pieceSelected) {
                Position from(inputData.positionFromX, inputData.positionFromY);
                Position to(clampedMouseXToGrid, clampedMouseYToGrid);
                this->userInputQueue->produce(std::make_shared<NormalMoveMessage>(
                        from, to
                ));
                deselectAllPieces();
            }
            else {
                inputData.positionFromX = clampedMouseXToGrid;
                inputData.positionFromY = clampedMouseYToGrid;
                selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, colors.normalMove);
                // NTH: pintar movimientos posibles
            }
            inputData.pieceSelected = !inputData.pieceSelected;
            break;
        case 's':
        case 'm':
            if (!inputData.pieceSelected){
                inputData.positionFromX = clampedMouseXToGrid;
                inputData.positionFromY = clampedMouseYToGrid;
                inputData.pieceSelected = true;
                inputData.firstEmptySelected = false;
                selectPiece(clampedMouseXToGrid,
                            clampedMouseYToGrid,
                            inputData.typeOfMove == 's' ? colors.splitMove : colors.mergeMove);
            } else if (!inputData.firstEmptySelected) {
                inputData.secondPositionX = clampedMouseXToGrid;
                inputData.secondPositionY = clampedMouseYToGrid;
                inputData.firstEmptySelected = true;
                if (inputData.typeOfMove == 'm')
                    selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, colors.mergeMove);
            } else {
                Position pos_1(inputData.positionFromX, inputData.positionFromY);
                Position pos_2(inputData.secondPositionX, inputData.secondPositionY);
                Position pos_3(clampedMouseXToGrid, clampedMouseYToGrid);

                (inputData.typeOfMove == 's') ?
                this->userInputQueue->produce(
                        std::make_shared<SplitMoveMessage>(
                                pos_1,
                                pos_2,
                                pos_3)) :
                this->userInputQueue->produce(
                        std::make_shared<MergeMoveMessage>(
                                pos_1,
                                pos_2,
                                pos_3));
                goToDefaultMovement();
            }
        default:
            break;
    }
}

void MainGameScreen::paintMoveSelectedNotification(const SDL_Color& color) {
    SDL_SetTextureAlphaMod(moveNotificationTexture->Get(), color.a);
    SDL_SetTextureColorMod(moveNotificationTexture->Get(), color.r, color.g, color.b);
}

void MainGameScreen::initColors() {
    this->colors.normalMove.r = 0;
    this->colors.normalMove.g = 255;
    this->colors.normalMove.b = 255;
    this->colors.normalMove.a = 75;

    this->colors.splitMove.r = 250;
    this->colors.splitMove.g = 15;
    this->colors.splitMove.b = 180;
    this->colors.splitMove.a = 255;

    this->colors.mergeMove.r = 0;
    this->colors.mergeMove.g = 128;
    this->colors.mergeMove.b = 0;
    this->colors.mergeMove.a = 150;

    this->colors.grey.r = 211;
    this->colors.grey.g = 211;
    this->colors.grey.b = 211;
    this->colors.grey.a = 255;

    this->colors.red.r = 255;
    this->colors.red.g = 0;
    this->colors.red.b = 0;
    this->colors.red.a = 255;

    this->colors.green.r = 0;
    this->colors.green.g = 255;
    this->colors.green.b = 0;
    this->colors.green.a = 255;
}

void MainGameScreen::goToDefaultMovement() {
    inputData.pieceSelected = false;
    inputData.firstEmptySelected = false;
    inputData.typeOfMove = 'n';
    deselectAllPieces();
    paintMoveSelectedNotification(colors.normalMove);
}

void MainGameScreen::loadMoveSelectedNotification(const int alpha) {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font, 12pt size
    SDL2pp::Font font("../assets/fonts/Vera.ttf", this->selectedPieceHeight * 2);

    // Render the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    moveNotificationTexture = std::make_unique<SDL2pp::Texture>(
            (*renderer),
            font.RenderText_Blended("*", SDL_Color{255, 255, 255, Uint8(alpha)}));

}

void MainGameScreen::loadBoardTextures() {
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
}

void MainGameScreen::setUserInputDefaultValues() {
    inputData.pieceSelected = false;
    inputData.firstEmptySelected = false;
    inputData.typeOfMove = 'n';
    inputData.positionFromX = 0;
    inputData.positionFromY = 0;
    inputData.secondPositionX = 0;
    inputData.secondPositionY = 0;
}

void MainGameScreen::startSDLWindow() {
    //sdl = std::make_unique<SDL2pp::SDL>((SDL_INIT_VIDEO | SDL_INIT_AUDIO));
    SDL2pp::SDL(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    this->window = std::make_unique<SDL2pp::Window>("Quantum Chess",
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    SDL_WINDOWPOS_UNDEFINED,
                                                    640,
                                                    480,
                                                    SDL_WINDOW_RESIZABLE);
    this->renderer = std::make_unique<SDL2pp::Renderer>((*window), -1, SDL_RENDERER_ACCELERATED);
}
