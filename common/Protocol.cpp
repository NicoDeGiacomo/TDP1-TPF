//
// Created by ale on 13/11/21.
//

#include "Protocol.h"
#include "ChatMessage.h"
#include "MoveMessage.h"
#include "SelectMessage.h"

#include <memory>

namespace Protocol {
    std::string MessageToString(const Message& message) {
        return message.getMessage();
    }
    std::unique_ptr<Message> StringToMessage(const std::string& string) {
        //TODO: return different types of message, use polymorphism
        if (string.at(0) == MESSAGE_REQUEST){
            return std::make_unique<ChatMessage>(string);
        } else if (string.at(0) == MOVE_REQUEST){
            return std::make_unique<MoveMessage>(string);
        } else if (string.at(0) == SELECT_REQUEST){
            return std::make_unique<SelectMessage>(string);
        }
        return std::make_unique<Message>(string);
    }
}