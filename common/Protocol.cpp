//
// Created by ale on 13/11/21.
//

#include "Protocol.h"
#include "messages/ChatMessage.h"
#include "messages/MoveMessage.h"
#include "messages/SelectMessage.h"

#include <memory>

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message) {
        return message->getMessage();
    }
    std::shared_ptr<Message> StringToMessage(const std::string& string, const std::string& id) {  // receive string id
        //TODO: return different types of message, use polymorphism
        if (string.at(0) == MESSAGE_REQUEST){
            return std::make_shared<ChatMessage>(string, id);
        } else if (string.at(0) == MOVE_REQUEST){
            return std::make_shared<MoveMessage>(string, id);
        } else if (string.at(0) == SELECT_REQUEST){
            return std::make_shared<SelectMessage>(string, id);
        }
        return std::make_shared<ChatMessage>(string, id);
    }
}