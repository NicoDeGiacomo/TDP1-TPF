#include "Protocol.h"
#include <ChatMessage.h>
#include <NormalMoveMessage.h>
#include <MergeMoveMessage.h>
#include <SplitMoveMessage.h>
#include <PlayerNameMessage.h>
#include <RoomIdMessage.h>
#include <PlayerTypeMessage.h>
#include <SeedMessage.h>
#include <stdexcept>
#include <iostream>

#include <memory>

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message) {
        return message->getMessage();
    }
    std::shared_ptr<Message> CharToMessage(char type) {
        if (type == CHAT_CHAR) {
            return std::make_shared<ChatMessage>();
        } else if (type == NORMAL_MOVE_CHAR) {
            return std::make_shared<NormalMoveMessage>();
        } else if (type == MERGE_MOVE_CHAR) {
            return std::make_shared<MergeMoveMessage>();
        } else if (type == SPLIT_MOVE_CHAR) {
            return std::make_shared<SplitMoveMessage>();
        } else if (type == PLAYER_NAME_CHAR) {
            return std::make_shared<PlayerNameMessage>();
        } else if (type == ROOM_ID_CHAR) {
            return std::make_shared<RoomIdMessage>();
        } else if (type == PLAYER_TYPE_CHAR) {
            return std::make_shared<PlayerTypeMessage>();
        } else if (type == SEED_CHAR) {
            return std::make_shared<SeedMessage>();
        }
        throw std::runtime_error("Unknown command in Protocol::CharToMessage. Char: " + type);
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
        } else if (type == PLAYER_NAME_CHAR) {
            return std::make_shared<PlayerNameMessage>(id);
        } else if (type == ROOM_ID_CHAR) {
            return std::make_shared<RoomIdMessage>(id);
        } else if (type == PLAYER_TYPE_CHAR) {
            return std::make_shared<PlayerTypeMessage>(id);
        } else if (type == SEED_CHAR) {
            return std::make_shared<SeedMessage>(id);
        }
        throw std::runtime_error("Unknown command in Protocol::CharToMessage. Char: " + type);
    }
}