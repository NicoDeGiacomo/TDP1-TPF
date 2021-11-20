//
// Created by ale on 20/11/21.
//

#include <SDL_image.h>
#include "MainGameScreen.h"

MainGameScreen::MainGameScreen(SDL2pp::Renderer &renderer, Board* board) : Screen(renderer) {
    this->_board = board;
    texturesMap.insert({BOARD_KEY, SDL2pp::Texture(renderer, BOARD_FILEPATH)});
    texturesMap.insert({PAWN_KEY, SDL2pp::Texture(renderer, PAWN_FILEPATH)});
    texturesMap.insert({ROOK_KEY, SDL2pp::Texture(renderer, ROOK_FILEPATH)});
    texturesMap.insert({KNIGHT_KEY, SDL2pp::Texture(renderer, KNIGHT_FILEPATH)});
    texturesMap.insert({BISHOP_KEY, SDL2pp::Texture(renderer, BISHOP_FILEPATH)});
    texturesMap.insert({KING_KEY, SDL2pp::Texture(renderer, KING_FILEPATH)});
    texturesMap.insert({QUEEN_KEY, SDL2pp::Texture(renderer, QUEEN_FILEPATH)});
    //renderer.Copy(texturesMap.at(PAWN_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);
    redraw();
}

int MainGameScreen::start() {
    return 0;
}

void MainGameScreen::redraw() {
    //todo: this shouldn't be hardcoded, also make 'redraw()' listen for screen resize
    int screenWidth = 640;
    int screenHeight = 480;
    int pieceWidth = screenWidth / 8;
    int pieceHeight = screenHeight / 8;
    // Clear screen
    renderer.Clear();

    renderer.Copy(texturesMap.at(BOARD_KEY), SDL2pp::NullOpt, SDL2pp::NullOpt);

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
