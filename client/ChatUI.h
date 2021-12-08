#ifndef QUANTUM_CHESS_CHATUI_H
#define QUANTUM_CHESS_CHATUI_H
#include <SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <deque>
#include "BlockingQueue.h"

#define CHAT_BACKGROUND_PNG "../assets/sprites/chatBackground.png"
#define CHAT_FONT_SIZE 15
#define CHAT_FONT_PADDING 11

class ChatUI {
private:
    std::unique_ptr<SDL2pp::Texture> inputMessageTexture;
    std::unique_ptr<SDL2pp::Texture> backgroundImageTexture;
    std::deque<std::unique_ptr<SDL2pp::Texture>> textures;
    SDL2pp::Renderer* _renderer;
    SDL2pp::Window* _window;
    const int yOffset = CHAT_FONT_SIZE + CHAT_FONT_PADDING * 2,
    xOffset = CHAT_FONT_SIZE + CHAT_FONT_PADDING;
    BlockingQueue<std::shared_ptr<std::string>> &chatQueue;

    std::deque<std::string> splitMessageIntoRenderableChunks(const std::string &basicString,
                                                             const SDL2pp::Font& font,
                                                             const char divider) const;
    void drawInputMessage(std::string& inputMessage);
public:
    ChatUI(BlockingQueue<std::shared_ptr<std::string>> &chatQueue);

    void renderMessages(std::string& inputMessage);

    void add(const std::string &message);

    bool clickInChat(int mouseX, int mouseY);

    void load(SDL2pp::Renderer *renderer, SDL2pp::Window *window);
};


#endif //QUANTUM_CHESS_CHATUI_H
