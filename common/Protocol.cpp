//
// Created by ale on 13/11/21.
//

#include "Protocol.h"

namespace Protocol {
    std::string MessageToString(Message message) {
        return message.getMessage();
    }
    Message StringToMessage(const std::string& string) {
        return Message(string);
    }
}