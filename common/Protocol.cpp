#include "Protocol.h"
#include "messages/ChatMessage.h"
#include "messages/NormalMoveMessage.h"
#include "messages/MergeMoveMessage.h"
#include "messages/SplitMoveMessage.h"
#include "messages/SelectMessage.h"
#include "messages/PlayerNameMessage.h"
#include <stdexcept>
#include <iostream>

#include <memory>

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message) {
        return message->getMessage();
    }
    // std::shared_ptr<Message> StringToMessage(const std::string& string, int id) {  // receive string id
    //     if (string.at(0) == CHAT_CHAR) {
    //         std::cout << "Sending CHAT MESSAGE\n";
    //         std::cout << "creating chat message" << string << std::endl;
    //         return std::make_shared<ChatMessage>(string.substr(1), id);
    //     } else if (string.at(0) == NORMAL_MOVE_CHAR) {
    //         std::cout << "Sending NORMAL_MOVE MESSAGE\n";
    //         std::cout << "creating normal message" << string << std::endl;
    //         return std::make_shared<NormalMoveMessage>(string.substr(1), id);
    //     } else if (string.at(0) == MERGE_MOVE_CHAR) {
    //         std::cout <<  "Sending MERGE_MOVE MESSAGE\n";
    //         return std::make_shared<MergeMoveMessage>(string.substr(1), id);
    //     } else if (string.at(0) == SPLIT_MOVE_CHAR) {
    //         std::cout << "Sending SPLIT_MOVE MESSAGE\n";
    //         return std::make_shared<SplitMoveMessage>(string.substr(1), id);
    //     } else if (string.at(0) == SELECT_CHAR) {
    //         std::cout << "Sending SELECT MESSAGE\n";
    //         return std::make_shared<SelectMessage>(string.substr(1), id);
    //     }
    //     throw std::runtime_error("Unknown command in Protocol");
    // }
    // size_t CharToMessageLenght(char c) {
    //     if (c == CHAT_CHAR) {
    //         return 2;
    //     } else if (c == NORMAL_MOVE_CHAR) {
    //         return 4;
    //     } else if (c == MERGE_MOVE_CHAR) {
    //         return 6;
    //     } else if (c == SPLIT_MOVE_CHAR) {
    //         return 6;
    //     } else if (c == SELECT_CHAR) {
    //         return 2;
    //     }
    //     throw std::runtime_error("Unknown command");  
    // }
    std::shared_ptr<Message> CharToMessage(char type) {
        if (type == CHAT_CHAR) {
            return std::make_shared<ChatMessage>();
        } else if (type == NORMAL_MOVE_CHAR) {
            return std::make_shared<NormalMoveMessage>();
        } else if (type == MERGE_MOVE_CHAR) {
            return std::make_shared<MergeMoveMessage>();
        } else if (type == SPLIT_MOVE_CHAR) {
            return std::make_shared<SplitMoveMessage>();
        } else if (type == SELECT_CHAR) {
            return std::make_shared<SelectMessage>();
        } else if (type == PLAYER_NAME_CHAR) {
            return std::make_shared<PlayerNameMessage>();
        }
        throw std::runtime_error("Unknown command in Protocol::CharToMessage");
    }
    std::shared_ptr<Message> CharToMessage(char type, int id) {
        if (type == CHAT_CHAR) {
            return std::make_shared<ChatMessage>(id);
        } else if (type == NORMAL_MOVE_CHAR) {
            return std::make_shared<NormalMoveMessage>(id);
        } else if (type == MERGE_MOVE_CHAR) {
            return std::make_shared<MergeMoveMessage>(id);
        } else if (type == SPLIT_MOVE_CHAR) {
            return std::make_shared<SplitMoveMessage>(id);
        } else if (type == SELECT_CHAR) {
            return std::make_shared<SelectMessage>(id);
        } else if (type == PLAYER_NAME_CHAR) {
            return std::make_shared<PlayerNameMessage>(id);
        }
        throw std::runtime_error("Unknown command in Protocol::CharToMessage");
    }
}