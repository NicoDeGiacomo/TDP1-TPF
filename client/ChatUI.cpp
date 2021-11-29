//
// Created by ale on 28/11/21.
//

#include "ChatUI.h"

ChatUI::ChatUI(SDL2pp::Renderer& renderer,
               const int x,
               const int width,
               const int height) : _renderer(renderer), _x(x), _width(width), _height(height) {
    /*for(int i = 0; i < 18; ++i) {
        add("hola mundo " + std::to_string(i));
    }*/
    //add("hhhhhhhhhhhhhhhh oooooooooooooooooo ooooooooooooooooo");
    backgroundImageTexture = std::make_unique<SDL2pp::Texture>(SDL2pp::Texture(_renderer, BACKGROUND_FILEPATH));
}
void ChatUI::drawInputMessage(std::string& inputMessage) {
    if (inputMessage.empty()) return;
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    SDL2pp::Font font("../assets/fonts/Vera.ttf", CHAT_FONT_SIZE);
    // add the text into new texture. Note that SDL_ttf render
    // text into Surface, which is converted into texture on the fly
    std::cout << "." << inputMessage << "." << std::endl;
    inputMessageTexture.reset();
    inputMessageTexture = std::make_unique<SDL2pp::Texture>(
            _renderer,
            font.RenderText_Blended(inputMessage,SDL_Color{
                    255,
                    255,
                    255,
                    255}));
    SDL2pp::Rect messageRect(
            _x + xOffset,
            _height - yOffset,
            inputMessageTexture->GetWidth(),
            inputMessageTexture->GetHeight()
    );
    _renderer.Copy((*inputMessageTexture), SDL2pp::NullOpt, messageRect);
}
void ChatUI::renderMessages(std::string& inputMessage) {
    // cola.popifnotempty
    _renderer.Copy((*backgroundImageTexture), SDL2pp::NullOpt, SDL2pp::Rect(_x, 0, _width, _height));
    drawInputMessage(inputMessage);

    int i = 1;
    auto texture = textures.begin();
    while (texture != textures.end()) {
        int y = _height - yOffset - i * (CHAT_FONT_SIZE + CHAT_FONT_PADDING);
        //if i cant render it, delete it from the queue
        if (y < 0) {
            texture = textures.erase(texture);
            continue;
        }
        SDL2pp::Rect messageRect(
                _x + xOffset,
                y,
                (*texture)->GetWidth(),
                (*texture)->GetHeight()
        );
        _renderer.Copy((**texture), SDL2pp::NullOpt, messageRect);
        ++texture;
        ++i;
    }
}

void ChatUI::add(const std::string &message) {
    // Initialize SDL_ttf library
    SDL2pp::SDLTTF ttf;
    // Load font
    SDL2pp::Font font("../assets/fonts/Vera.ttf", CHAT_FONT_SIZE);
    std::deque<std::string> tinyMessages = splitMessageIntoRenderableChunks(message, font, ' ');
    auto firstMessage = tinyMessages.begin();
    while (firstMessage != tinyMessages.end()) {
        // add the text into new texture. Note that SDL_ttf render
        // text into Surface, which is converted into texture on the fly
        std::cout << "." << (*firstMessage) << "." << std::endl;
        textures.push_front(std::make_unique<SDL2pp::Texture>(
                _renderer,
                font.RenderText_Blended((*firstMessage),SDL_Color{
                    255,
                    255,
                    255,
                    255})));
        firstMessage = tinyMessages.erase(firstMessage);
    }
}

std::deque<std::string> ChatUI::splitMessageIntoRenderableChunks(const std::string &message,
                                                                 const SDL2pp::Font& font,
                                                                 const char divider) const {
    std::string bufferMessage(message);
    int messageWidth, messageHeight;
    std::deque<std::string> chunks;
    TTF_SizeText(font.Get(), bufferMessage.c_str(), &messageWidth, &messageHeight);
    while (messageWidth >= _width) {
        //split to last backspace, add to chunks
        size_t length = bufferMessage.length();
        size_t pos = bufferMessage.find_last_of(divider);
        //failed to find a divider char
        if (pos == std::string::npos) {
            break;
        }
        chunks.push_front(bufferMessage.substr(pos, length));
        bufferMessage.erase(pos, length);
        TTF_SizeText(font.Get(), bufferMessage.c_str(), &messageWidth, &messageHeight);
    }
    chunks.push_front(bufferMessage);
    return chunks;
}

bool ChatUI::clickInChat(int mouseX, int mouseY) {
    return mouseX > _x && mouseY > 0 && mouseY <  _height;
}
