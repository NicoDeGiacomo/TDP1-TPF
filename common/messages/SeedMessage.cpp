#include "SeedMessage.h"
#include "Protocol.h"
#include <iostream>
#include <string.h>

/***********************
    Metodos publicos
************************/

SeedMessage::SeedMessage(int id) : Message(id) {
    this->type = SEED_CHAR;
    this->_msg_len = sizeof(unsigned int);
}

SeedMessage::SeedMessage(unsigned int seed) {
    this->type = SEED_CHAR;
    this->_msg_len = sizeof(unsigned int);
    _message.reserve(_msg_len);
    memcpy((void *) _message.data(), &seed, _msg_len);
    _message = std::string(_message.data(), _msg_len);
}

void SeedMessage::apply(Board&, Chat &) const {
    // throw std::runtime_error("This method should not be called");
}
