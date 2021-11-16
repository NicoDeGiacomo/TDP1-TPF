//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_PROTOCOL_H
#define QUANTUM_CHESS_PROTOCOL_H

#include <string>
#include <Message.h>
#include <memory>

#define SELECT_REQUEST 's'
#define MOVE_REQUEST 'o'
#define MESSAGE_REQUEST 'm'

namespace Protocol {
    std::string MessageToString(const Message& message);
    std::unique_ptr<Message> StringToMessage(const std::string& string);
}
#endif //QUANTUM_CHESS_PROTOCOL_H
