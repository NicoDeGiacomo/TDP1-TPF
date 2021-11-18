//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_PROTOCOL_H
#define QUANTUM_CHESS_PROTOCOL_H

#include <string>
#include <messages/Message.h>
#include <memory>

#define SELECT_REQUEST 's'
#define MOVE_REQUEST 'o'
#define MESSAGE_REQUEST 'm'

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message);
    std::shared_ptr<Message> StringToMessage(const std::string& string, const std::string& id);
}
#endif //QUANTUM_CHESS_PROTOCOL_H
