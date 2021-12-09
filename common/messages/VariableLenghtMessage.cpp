#include <VariableLenghtMessage.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>

VariableLenghtMessage::VariableLenghtMessage(int id) : Message(id) {}

VariableLenghtMessage::VariableLenghtMessage(const std::string &message, int id)
                                            : Message(message, id) {}

const std::string VariableLenghtMessage::getEncodedMessage() const {
    unsigned short int len = htons(_message.size());
    char len_arr[2];
    memcpy(len_arr, &len, 2);
    std::string encoded_message;
    encoded_message.push_back(len_arr[0]);
    encoded_message.push_back(len_arr[1]);
    encoded_message += _message;

    return encoded_message;
}

int VariableLenghtMessage::getBytesToRead() {
    if (_msg_len == 0)
        return sizeof(unsigned short int);
    if (this->_message.size() > 0)
        return 0;
    return _msg_len;
}

void VariableLenghtMessage::decode(std::vector<char> &buf) {
    if (_msg_len == 0) {
        unsigned short int name_len_be;
        memcpy(&name_len_be, buf.data(), sizeof(unsigned short int));
        _msg_len = ntohs(name_len_be);
    } else {
        this->_message = std::string(buf.data(), _msg_len);
    }
}
