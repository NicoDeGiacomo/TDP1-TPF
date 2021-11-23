//
// Created by ale on 13/11/21.
//

#include "Protocol.h"
#include "messages/ChatMessage.h"
#include "messages/NormalMoveMessage.h"
#include "messages/MergeMoveMessage.h"
#include "messages/SplitMoveMessage.h"
#include "messages/SelectMessage.h"
#include <stdexcept>
#include <iostream>

#include <memory>

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message) {
        return message->getMessage();
    }
    std::shared_ptr<Message> StringToMessage(const std::string& string, int id) {  // receive string id
        if (string.at(0) == CHAT_CHAR) {
            std::cout << "Sending CHAT MESSAGE\n";
            std::cout << "creating chat message" << string << std::endl;
            return std::make_shared<ChatMessage>(string, id);
        } else if (string.at(0) == NORMAL_MOVE_CHAR) {
            std::cout << "Sending NORMAL_MOVE MESSAGE\n";
            std::cout << "creating normal message" << string << std::endl;
            return std::make_shared<NormalMoveMessage>(string, id);
        } else if (string.at(0) == MERGE_MOVE_CHAR) {
            std::cout << "Sending MERGE_MOVE MESSAGE\n";
            return std::make_shared<MergeMoveMessage>(string, id);
        } else if (string.at(0) == SPLIT_MOVE_CHAR) {
            std::cout << "Sending SPLIT_MOVE MESSAGE\n";
            return std::make_shared<SplitMoveMessage>(string, id);
        } else if (string.at(0) == SELECT_CHAR) {
            std::cout << "Sending SELECT MESSAGE\n";
            return std::make_shared<SelectMessage>(string, id);
        }
        throw std::runtime_error("Unknown command");
    }
    size_t CharToMessageLenght(char c) {
        if (c == CHAT_CHAR) {
            return 2;
        } else if (c == NORMAL_MOVE_CHAR) {
            return 4;
        } else if (c == MERGE_MOVE_CHAR) {
            return 6;
        } else if (c == SPLIT_MOVE_CHAR) {
            return 6;
        } else if (c == SELECT_CHAR) {
            return 2;
        }
        throw std::runtime_error("Unknown command");  
    }

}