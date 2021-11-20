//
// Created by ale on 20/11/21.
//

#include <SDL_image.h>
#include "MainGameScreen.h"

MainGameScreen::MainGameScreen(SDL2pp::Renderer &renderer, Board* board) : Screen(renderer) {
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
