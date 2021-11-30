//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_PROTOCOL_H
#define QUANTUM_CHESS_PROTOCOL_H

#include <string>
#include <messages/Message.h>
#include <memory>

// #define SELECT_REQUEST 's'
// #define MOVE_REQUEST 'o'
// #define MESSAGE_REQUEST 'm'

#define CHAT_CHAR 'c'
#define NORMAL_MOVE_CHAR 'n'
#define SPLIT_MOVE_CHAR 's'
#define MERGE_MOVE_CHAR 'm'
#define SELECT_CHAR 's'
#define WHITE_CHAR 'W'
#define BLACK_CHAR 'B'
#define SPECTATOR_CHAR 'O'


namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message);
    std::shared_ptr<Message> StringToMessage(const std::string& string, int id);
    size_t CharToMessageLenght(char c);
}
#endif //QUANTUM_CHESS_PROTOCOL_H
