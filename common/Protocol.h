//
// Created by ale on 13/11/21.
//

#ifndef QUANTUM_CHESS_PROTOCOL_H
#define QUANTUM_CHESS_PROTOCOL_H

#include <string>
#include <Message.h>


namespace Protocol {
    std::string MessageToString(Message message);
    Message StringToMessage(const std::string& string);
}
#endif //QUANTUM_CHESS_PROTOCOL_H
