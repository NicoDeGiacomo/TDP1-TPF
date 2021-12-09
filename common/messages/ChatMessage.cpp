#include <iostream>
#include "ChatMessage.h"
#include "Protocol.h"
#include <string.h>
#include <arpa/inet.h>

/***********************
    Metodos publicos
************************/

ChatMessage::ChatMessage(int id) : VariableLenghtMessage(id) {
    this->type = CHAT_CHAR;
}

ChatMessage::ChatMessage(const std::string &message, int id) : VariableLenghtMessage(message, id) {
    this->type = CHAT_CHAR;
}

void ChatMessage::apply(Board&) const {
    if (this->id == -1)
        std::cout << "This user added a message to chat. Message: " 
                    << _message << std::endl;
    else
        std::cout << "User " << this->id << " added a message to chat. Message: " 
                    << _message << std::endl;
}

void ChatMessage::apply(Board&, Chat &chat) const {
    chat.addMessage(this->id, this->_message);
}
