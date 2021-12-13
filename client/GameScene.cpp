#include <NormalMove.h>
#include <NormalMoveMessage.h>
#include <thread>
#include <SplitMoveMessage.h>
#include <MergeMoveMessage.h>
#include <ChatMessage.h>
#include <StageMode.h>
#include "GameScene.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>

GameScene::GameScene(Board& board,
                     BlockingQueue<std::shared_ptr<Message>>* userInputQueue,
                     BlockingQueue<std::shared_ptr<std::string>> &chatQueue,
                     char playerType, bool& gameFinished, bool mute)
                   : _board(board), _gameFinished(gameFinished), mute(mute) {
    this->initColors();
    this->chatUI = std::make_unique<ChatUI>(chatQueue);
    this->userInputQueue = userInputQueue;
    this->setUserInputDefaultValues();
    this->_playerType = playerType;
}

void GameScene::updateLoop() {
    this->handleEvents();
    if (_gameFinished || _board.isFinished()) {
        _gameFinished = true;
        endMessage(SPECTATOR_CHAR);
        return;
    }
    Uint32 deltaTime = Timer::partial();
    //wait if not enough time has passed for it to render another frame
    if (deltaTime < TIME_BETWEEN_FRAMES)
        SDL_Delay(TIME_BETWEEN_FRAMES - deltaTime);
    this->render();
    //time since previous render is 0 again
    Timer::reset();
}

void GameScene::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN)
            whereDidMouseClicked();
        inputData.chatClicked ? manageChatEvent(event) : manageBoardEvent(event);
    }
}

void GameScene::render() {
    //clear screen
    _renderer->Clear();
    //render board
    _renderer->Copy(texturesMap.at(BOARD_KEY), SDL2pp::NullOpt, SDL2pp::Rect(0,0,_window->GetHeight(),_window->GetHeight()));
    //render the higlight of entangled pieces
    for (auto &position : splitsOfSamePiece){
        Piece *piece = _board.getPiece(position);
        int piecePositionX = position.getX() - 1;
        int piecePositionY = position.getY() - 1;
        if (_playerType == WHITE_CHAR){
            piecePositionY = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionY;
        } else {
            piecePositionX = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionX;
        }
        int x = piecePositionX * pieceSize + (pieceSize - selectedPieceSize)/2;
        int y = piecePositionY * pieceSize + (pieceSize - selectedPieceSize)/2;
        SDL2pp::Rect pieceRect(
                x,
                y,
                selectedPieceSize,
                selectedPieceSize);
        _renderer->Copy(samePieceSplitTextureMap.at(toupper(piece->getDrawing())), SDL2pp::NullOpt, pieceRect);
    }
    for (auto &position : entangledPiecesPosition) {
        Piece *piece = _board.getPiece(position);
        //the -1 are for the screen offset
        int piecePositionX = piece->getPosition().getX() - 1;
        int piecePositionY = piece->getPosition().getY() - 1;
        if (_playerType == WHITE_CHAR){
            piecePositionY = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionY;
        } else {
            piecePositionX = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionX;
        }
        int x = piecePositionX * pieceSize + (pieceSize - selectedPieceSize)/2;
        int y = piecePositionY * pieceSize + (pieceSize - selectedPieceSize)/2;
        SDL2pp::Rect pieceRect(
                x,
                y,
                selectedPieceSize,
                selectedPieceSize);
        _renderer->Copy(entangledTexturesMap.at(toupper(piece->getDrawing())), SDL2pp::NullOpt, pieceRect);
    }
    //render the highlight of selected pieces
    for (auto &piece : selectedPieces) {
        //the -1 are for the screen offset
        int piecePositionX = piece->getPosition().getX() - 1;
        int piecePositionY = piece->getPosition().getY() - 1;
        if (_playerType == WHITE_CHAR){
            piecePositionY = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionY;
        } else {
            piecePositionX = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionX;
        }
        int x = piecePositionX * pieceSize + (pieceSize - selectedPieceSize)/2;
        int y = piecePositionY * pieceSize + (pieceSize - selectedPieceSize)/2;
        SDL2pp::Rect pieceRect(
                x,
                y,
                selectedPieceSize,
                selectedPieceSize);
        _renderer->Copy(selectedTexturesMap.at(toupper(piece->getDrawing())), SDL2pp::NullOpt, pieceRect);
    }
    //render pieces
    for (const auto &piece : _board) {
        //the -1 are for the screen offset
        int piecePositionX = piece->getPosition().getX() - 1;
        int piecePositionY = piece->getPosition().getY() - 1;
        if (_playerType == WHITE_CHAR){
            piecePositionY = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionY;
        } else {
            piecePositionX = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionX;
        }
        int x = piecePositionX * pieceSize;
        int y = piecePositionY * pieceSize;
        SDL2pp::Rect pieceRect(
                x,
                y,
                pieceSize,
                pieceSize);
        _renderer->Copy(texturesMap.at(piece->getDrawing()), SDL2pp::NullOpt, pieceRect);
        float pieceProbability = piece->getProbability();
        //dont show probability bar of normal pieces
        if (pieceProbability == 0 || pieceProbability == 1)
            continue;
        int probabilityBarWidth = pieceSize * PROBABILITY_BAR_WIDTH_MULTIPLIER;
        int probabilityBarOffsetX = (pieceSize - probabilityBarWidth) / 2;
        renderProbabilityBar(
                x + probabilityBarOffsetX,
                y,
                probabilityBarWidth,
                pieceSize * PROBABILITY_BAR_HEIGHT_MULTIPLIER,
                pieceProbability,
                colors.darkGreen,
                colors.darkRed,
                colors.grey);
    }
    for(auto& position : possibleMoves){
        //the -1 are for the screen offset
        int piecePositionX = position.getX() - 1;
        int piecePositionY = position.getY() - 1;
        if (_playerType == WHITE_CHAR){
            piecePositionY = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionY;
        } else {
            piecePositionX = BOARD_SQUARES_IN_A_LINE - 1 - piecePositionX;
        }
        int x = piecePositionX * pieceSize;
        int y = piecePositionY * pieceSize;
        SDL2pp::Rect possibleMoveRect(
                x,
                y,
                pieceSize,
                pieceSize);
        _renderer->Copy((*dotTexture), SDL2pp::NullOpt, possibleMoveRect);
    }

    chatUI->renderMessages(inputData.message);

    //render move notification text
    SDL2pp::Rect moveNotificationRect(
            _window->GetHeight(),
            -moveNotificationTexture->GetHeight() / 8, //place the '*' on the top left of chat
            moveNotificationTexture->GetWidth(),
            moveNotificationTexture->GetHeight()
    );
    _renderer->Copy((*moveNotificationTexture), SDL2pp::NullOpt, moveNotificationRect);

    //render turn notification text
    paintTurnNotification((_board.getCurrentTurn() == PieceColor::WHITE) ? colors.white : colors.black);
    int chatWidth = _window->GetWidth() - _window->GetHeight();
    SDL2pp::Rect turnNotificationRect(
            _window->GetHeight() + chatWidth - turnNotificationTexture->GetWidth(),
            -turnNotificationTexture->GetHeight() / 8, //place the '*' on the top right of chat
            turnNotificationTexture->GetWidth(),
            turnNotificationTexture->GetHeight()
    );
    _renderer->Copy((*turnNotificationTexture), SDL2pp::NullOpt, turnNotificationRect);

    //show rendered frame
    _renderer->Present();
}
void GameScene::renderProbabilityBar(const int x,
                                     const int y,
                                     const int width,
                                     const int height,
                                     float percent,
                                     const SDL_Color frontColor,
                                     const SDL_Color backgroundColor,
                                     const SDL_Color edgeColor) {
    //check if percent is valid, between 0 and 1
    percent = percent > 1.f ? 1.f : percent < 0.f ? 0.f : percent;
    //edge size is 1/3 of the bar height
    int edgeSize = height / 3;
    int frontWidth = (int)((float)(width - edgeSize * 2) * percent);
    SDL2pp::Rect backgroundRect(x, y, width, height);
    SDL2pp::Rect frontRect(x + edgeSize, y, frontWidth, height);
    SDL2pp::Rect topEdge(x, y, width, edgeSize);
    SDL2pp::Rect bottomEdge(x, y + height, width, edgeSize);
    SDL2pp::Rect rightEdge(x + width - edgeSize, y, edgeSize, height);
    SDL2pp::Rect leftEdge(x, y, edgeSize, height);
    //blend mode so can overlap pixel colors based on alpha value
    _renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    _renderer->SetDrawColor(backgroundColor);
    _renderer->FillRect(backgroundRect);
    _renderer->SetDrawColor(frontColor);
    _renderer->FillRect(frontRect);
    //edges
    _renderer->SetDrawColor(edgeColor);
    _renderer->FillRect(topEdge);
    _renderer->FillRect(bottomEdge);
    _renderer->FillRect(rightEdge);
    _renderer->FillRect(leftEdge);
    //back to none blend mode
    _renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE);
}

void GameScene::selectPiece(const int x, const int y, const SDL_Color& color, bool merge) {
    Piece* piece = _board.getPiece(Position(x,y));
    if (!piece)
        return;
    selectedPieces.push_front(piece);
    SDL2pp::Texture &texture = selectedTexturesMap.at(toupper(piece->getDrawing()));
    texture.SetColorAndAlphaMod(color);
    loadPossibleMoves(piece, color, merge);
    showEntangledPieces(piece);
    showSamePieceSplits(piece);
}

void GameScene::deselectAllPieces() {
    selectedPieces.clear();
    entangledPiecesPosition.clear();
    possibleMoves.clear();
    splitsOfSamePiece.clear();
}

void GameScene::paintMoveSelectedNotification(const SDL_Color& color) {
    moveNotificationTexture->SetColorAndAlphaMod(color);
}

void GameScene::initColors() {
    this->colors.normalMove.r = 0;
    this->colors.normalMove.g = 255;
    this->colors.normalMove.b = 255;
    this->colors.normalMove.a = 255;

    this->colors.splitMove.r = 250;
    this->colors.splitMove.g = 15;
    this->colors.splitMove.b = 180;
    this->colors.splitMove.a = 255;

    this->colors.mergeMove.r = 0;
    this->colors.mergeMove.g = 128;
    this->colors.mergeMove.b = 0;
    this->colors.mergeMove.a = 255;

    this->colors.grey.r = 177;
    this->colors.grey.g = 177;
    this->colors.grey.b = 177;
    this->colors.grey.a = 255;

    this->colors.darkRed.r = 200;
    this->colors.darkRed.g = 0;
    this->colors.darkRed.b = 0;
    this->colors.darkRed.a = 255;

    this->colors.darkGreen.r = 0;
    this->colors.darkGreen.g = 200;
    this->colors.darkGreen.b = 0;
    this->colors.darkGreen.a = 255;

    this->colors.entangled.r = 127;
    this->colors.entangled.g = 0;
    this->colors.entangled.b = 255;
    this->colors.entangled.a = 255;

    this->colors.samePiece.r = 106;
    this->colors.samePiece.g = 13;
    this->colors.samePiece.b = 173;
    this->colors.samePiece.a = 255;

    this->colors.white.r = 255;
    this->colors.white.g = 255;
    this->colors.white.b = 255;
    this->colors.white.a = 255;

    this->colors.black.r = 0;
    this->colors.black.g = 0;
    this->colors.black.b = 0;
    this->colors.black.a = 255;
}

void GameScene::goToDefaultMovement() {
    inputData.pieceSelected = false;
    inputData.firstEmptySelected = false;
    inputData.typeOfMove = 'n';
    deselectAllPieces();
    paintMoveSelectedNotification(colors.normalMove);
}

void GameScene::loadNotifications() {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font, 12pt size
    SDL2pp::Font font("../assets/fonts/Vera.ttf", this->selectedPieceSize * 2);

    // Render the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    moveNotificationTexture = std::make_unique<SDL2pp::Texture>(
            (*_renderer),
            font.RenderText_Blended("*", SDL_Color{255, 255, 255, 255}));
    turnNotificationTexture = std::make_unique<SDL2pp::Texture>(
            (*_renderer),
            font.RenderText_Blended("*", SDL_Color{255, 255, 255, 255}));
}

void GameScene::loadBoardTextures() {
    texturesMap.insert({BOARD_KEY, SDL2pp::Texture((*_renderer), BOARD_PNG)});

    texturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*_renderer), WHITE_PAWN_PNG)});
    texturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*_renderer), WHITE_ROOK_PNG)});
    texturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*_renderer), WHITE_KNIGHT_PNG)});
    texturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*_renderer), WHITE_BISHOP_PNG)});
    texturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*_renderer), WHITE_KING_PNG)});
    texturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*_renderer), WHITE_QUEEN_PNG)});

    texturesMap.insert({BLACK_PAWN_KEY, SDL2pp::Texture((*_renderer), BLACK_PAWN_PNG)});
    texturesMap.insert({BLACK_ROOK_KEY, SDL2pp::Texture((*_renderer), BLACK_ROOK_PNG)});
    texturesMap.insert({BLACK_KNIGHT_KEY, SDL2pp::Texture((*_renderer), BLACK_KNIGHT_PNG)});
    texturesMap.insert({BLACK_BISHOP_KEY, SDL2pp::Texture((*_renderer), BLACK_BISHOP_PNG)});
    texturesMap.insert({BLACK_KING_KEY, SDL2pp::Texture((*_renderer), BLACK_KING_PNG)});
    texturesMap.insert({BLACK_QUEEN_KEY, SDL2pp::Texture((*_renderer), BLACK_QUEEN_PNG)});

    selectedTexturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*_renderer), SELECTED_PAWN_PNG)});
    selectedTexturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*_renderer), SELECTED_ROOK_PNG)});
    selectedTexturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*_renderer), SELECTED_KNIGHT_PNG)});
    selectedTexturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*_renderer), SELECTED_BISHOP_PNG)});
    selectedTexturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*_renderer), SELECTED_KING_PNG)});
    selectedTexturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*_renderer), SELECTED_QUEEN_PNG)});

    entangledTexturesMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*_renderer), SELECTED_PAWN_PNG)});
    entangledTexturesMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*_renderer), SELECTED_ROOK_PNG)});
    entangledTexturesMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*_renderer), SELECTED_KNIGHT_PNG)});
    entangledTexturesMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*_renderer), SELECTED_BISHOP_PNG)});
    entangledTexturesMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*_renderer), SELECTED_KING_PNG)});
    entangledTexturesMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*_renderer), SELECTED_QUEEN_PNG)});

    for (auto& texture : entangledTexturesMap) {
        texture.second.SetColorAndAlphaMod(colors.entangled);
    }

    samePieceSplitTextureMap.insert({WHITE_PAWN_KEY, SDL2pp::Texture((*_renderer), SELECTED_PAWN_PNG)});
    samePieceSplitTextureMap.insert({WHITE_ROOK_KEY, SDL2pp::Texture((*_renderer), SELECTED_ROOK_PNG)});
    samePieceSplitTextureMap.insert({WHITE_KNIGHT_KEY, SDL2pp::Texture((*_renderer), SELECTED_KNIGHT_PNG)});
    samePieceSplitTextureMap.insert({WHITE_BISHOP_KEY, SDL2pp::Texture((*_renderer), SELECTED_BISHOP_PNG)});
    samePieceSplitTextureMap.insert({WHITE_KING_KEY, SDL2pp::Texture((*_renderer), SELECTED_KING_PNG)});
    samePieceSplitTextureMap.insert({WHITE_QUEEN_KEY, SDL2pp::Texture((*_renderer), SELECTED_QUEEN_PNG)});

    for (auto& texture : samePieceSplitTextureMap) {
        texture.second.SetColorAndAlphaMod(colors.samePiece);
    }
}

void GameScene::setUserInputDefaultValues() {
    inputData.chatClicked = false;
    inputData.message = "";
    inputData.pieceSelected = false;
    inputData.firstEmptySelected = false;
    inputData.typeOfMove = 'n';
    inputData.positionFromX = 0;
    inputData.positionFromY = 0;
    inputData.secondPositionX = 0;
    inputData.secondPositionY = 0;
}

void GameScene::handleBoardClick() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    int clampedMouseXToGrid = ceil((float)mouseX / pieceSize);
    int clampedMouseYToGrid = ceil((float)mouseY / pieceSize);
    if (_playerType == WHITE_CHAR){
        clampedMouseYToGrid = BOARD_SQUARES_IN_A_LINE + 1 - clampedMouseYToGrid;
    } else {
        clampedMouseXToGrid = BOARD_SQUARES_IN_A_LINE + 1 - clampedMouseXToGrid;
    }
    switch (inputData.typeOfMove) {
        case 'n':
            if (inputData.pieceSelected) {
                if (canMovePiece()) {
                    Position from(inputData.positionFromX, inputData.positionFromY);
                    Position to(clampedMouseXToGrid, clampedMouseYToGrid);
                    this->userInputQueue->produce(std::make_shared<NormalMoveMessage>(
                            from, to
                    ));
                    _mixer->PlayChannel(-1, *(*_sound)[1]);
                }
                deselectAllPieces();
            }
            else {
                inputData.positionFromX = clampedMouseXToGrid;
                inputData.positionFromY = clampedMouseYToGrid;
                selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, colors.normalMove);
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
                            inputData.typeOfMove == 's' ? colors.splitMove : colors.mergeMove,
                            inputData.typeOfMove != 's');
            } else if (!inputData.firstEmptySelected) {
                inputData.secondPositionX = clampedMouseXToGrid;
                inputData.secondPositionY = clampedMouseYToGrid;
                inputData.firstEmptySelected = true;
                if (inputData.typeOfMove == 'm')
                    selectPiece(clampedMouseXToGrid, clampedMouseYToGrid, colors.mergeMove, true);
            } else {
                if (canMovePiece()) {
                    Position pos_1(inputData.positionFromX, inputData.positionFromY);
                    Position pos_2(inputData.secondPositionX, inputData.secondPositionY);
                    Position pos_3(clampedMouseXToGrid, clampedMouseYToGrid);

                    if (inputData.typeOfMove == 's'){
                    this->userInputQueue->produce(
                            std::make_shared<SplitMoveMessage>(
                                    pos_1,
                                    pos_2,
                                    pos_3));
                        _mixer->PlayChannel(-1, *(*_sound)[1], 2);
                    } else{  
                    this->userInputQueue->produce(
                            std::make_shared<MergeMoveMessage>(
                                    pos_1,
                                    pos_2,
                                    pos_3));
                        _mixer->PlayChannel(-1, *(*_sound)[1]);
                    }
                }
                goToDefaultMovement();
            }
        default:
            break;
    }
}

void GameScene::manageBoardEvent(SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            StageMode::log("GAME FINISHED");
            _gameFinished = true;
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: case SDLK_q:
                    StageMode::log("GAME FINISHED");
                    _gameFinished = true;
                    return;
                case SDLK_n:
                    StageMode::log("You pressed the Normal Move key");
                    inputData.typeOfMove = 'n';
                    //normalMove move selection color
                    paintMoveSelectedNotification(colors.normalMove);
                    break;
                case SDLK_s:
                    StageMode::log("You pressed the Split Move key");
                    inputData.typeOfMove = 's';
                    //split move selection color
                    paintMoveSelectedNotification(colors.splitMove);
                    break;
                case SDLK_m:
                    StageMode::log("You pressed the Merge Move key");
                    inputData.typeOfMove = 'm';
                    //merge move selection color
                    paintMoveSelectedNotification(colors.mergeMove);
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            handleBoardClick();
    }
}

void GameScene::manageChatEvent(SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            //Handle backspace
            if( event.key.keysym.sym == SDLK_BACKSPACE && inputData.message.length() > 0 ) {
                inputData.message.pop_back();
            }
                //Handle copy
            else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
                SDL_SetClipboardText( inputData.message.c_str() );
            }
                //Handle paste
            else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
                inputData.message += SDL_GetClipboardText();
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                if (inputData.message.empty()) break;
                this->userInputQueue->produce(
                        std::make_shared<ChatMessage>(inputData.message));
                inputData.message = "";
            } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                StageMode::log("GAME FINISHED");
                _gameFinished = true;
                return;
            }
            break;
        case SDL_QUIT:
            StageMode::log("GAME FINISHED");
            _gameFinished = true;
            return;
        case SDL_TEXTINPUT:
            /* Add new text onto the end of our text */
            inputData.message += event.text.text;
            break;
    }
}

void GameScene::whereDidMouseClicked() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    inputData.chatClicked = chatUI->clickInChat(mouseX, mouseY);
}

void GameScene::loadPossibleMoves(const Piece* piece, const SDL_Color& color, bool merge) {
    if (!piece)
        return;
    if (!possibleMoves.empty()){
        //inner join of possible moves
        auto newPossibleMoves = piece->getPossibleMoves(merge);
        auto possibleMove = possibleMoves.begin();
        while (possibleMove != possibleMoves.end()){
            bool found = (std::find(
                    newPossibleMoves.begin(),
                    newPossibleMoves.end(),
                    (*possibleMove)) != newPossibleMoves.end());
            if (found){
                ++possibleMove;
                continue;
            }
            possibleMove = possibleMoves.erase(possibleMove);
        }

    } else {
        possibleMoves = piece->getPossibleMoves(merge);
        dotTexture->SetColorMod(color.r, color.g, color.b);
    }
}

void GameScene::showEntangledPieces(Piece *piece) {
    auto newEntangledPieces = piece->getEntanglements();
    if (!entangledPiecesPosition.empty())
        copy(
            newEntangledPieces.rbegin(),
            newEntangledPieces.rend(),
            front_inserter(entangledPiecesPosition));
    else
        entangledPiecesPosition = newEntangledPieces;
}

void GameScene::endMessage(char end_state) {
    //todo: fix this messages
    std::string message;
    if (end_state == BLACK_CHAR){
        message = "FIN DE LA PARTIDA\nGANASTE!";
    } else if (end_state == WHITE_CHAR){
        message = "FIN DE LA PARTIDA\nPERDISTE:(";
    } else {
        message = "FIN DE LA PARTIDA\n";
    }
    
    const SDL_MessageBoxButtonData buttons[] = {
    { /* .flags, .buttonid, .text */        0, 1, "download game" },
    { /* .flags, .buttonid, .text */        0, 0, "close" }
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 199, 201, 200},
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   18, 18, 18},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 116, 212, 208 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   199, 201, 200 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 115, 8, 8  }
        }
    };

    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "Quamtum Chess", /* .title */
        message.c_str(), /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    SDL_ShowMessageBox(&messageboxdata, &buttonid);
    if (buttonid == 1){
        _board.generateDump();
    }
}

bool GameScene::canMovePiece() {
    if (_playerType == WHITE_CHAR && _board.getCurrentTurn() == PieceColor::WHITE)
        return true;
    if (_playerType == BLACK_CHAR && _board.getCurrentTurn() == PieceColor::BLACK)
        return true;
    return false;
}

void GameScene::load(SDL2pp::Renderer *renderer, SDL2pp::Window *window) {
    Scene::load(renderer, window);
    if (!this->mute)
        _mixer->PlayChannel(1, *(*_sound)[0], -1);
    _mixer->SetVolume(1, 55);
    this->pieceSize = _window->GetHeight() / BOARD_SQUARES_IN_A_LINE;
    this->selectedPieceSize = _window->GetHeight() / (BOARD_SQUARES_IN_A_LINE - 1); // -1 to be able to highlight it
    //load scene, but dont process input nor render textures
    this->chatUI->load(_renderer, _window);
    this->loadBoardTextures();
    this->loadNotifications();
    this->paintMoveSelectedNotification(colors.normalMove);
    this->dotTexture = std::make_unique<SDL2pp::Texture>((*_renderer), DOT_PNG);
    this->dotTexture->SetAlphaMod(100);
    this->render();
}

void GameScene::paintTurnNotification(SDL_Color &color) {
    turnNotificationTexture->SetColorAndAlphaMod(color);
}

void GameScene::showSamePieceSplits(Piece *piece) {
    splitsOfSamePiece = piece->getSplits();
}
