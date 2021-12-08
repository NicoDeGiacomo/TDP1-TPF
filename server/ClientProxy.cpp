#include "ClientProxy.h"
#include "Socket.h"
#include "Message.h"
#include "ChatMessage.h"
#include "NormalMoveMessage.h"
#include "SplitMoveMessage.h"
#include "MergeMoveMessage.h"
#include "Protocol.h"
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <string.h>


// #define CHAT_CHAR 'c'
// #define NORMAL_MOVE_CHAR 'n'
// #define SPLIT_MOVE_CHAR 's'
// #define MERGE_MOVE_CHAR 'm'

/***********************
    Metodos privados
************************/

unsigned short int ClientProxy::decodeChatMessageLen() {
    std::cout << "start decoding chat message" << std::endl;
    char _msg_len[2];
    socket.receive(_msg_len, 2);
    unsigned short int name_len_be;
    memcpy(&name_len_be, _msg_len, 2);
    unsigned short int msg_len = ntohs(name_len_be);
    return msg_len;
}

std::string ClientProxy::recvMessage(unsigned short int msg_len) {
    std::vector<char> msg;
    msg.reserve(msg_len);
    char *buf = &msg[0];
    socket.receive(buf, msg_len);
    std::string msg_str(buf, msg_len);
    return msg_str;
}


// Message ProxyClient::decodeNormalMoveMessage() {
    
// }

// Message ProxyClient::decodeSplitMoveMessage() {
    
// }

// Message ProxyClient::decodeMergeMoveMessage() {
    
// }

/***********************
    Metodos publicos
************************/

ClientProxy::ClientProxy() : id(-1) {}

ClientProxy::ClientProxy(Socket &socket, int id, char type, unsigned int seed)
                        : socket(std::move(socket)), is_player(false), id(id) {
    this->socket.send(&type, 1);
    this->socket.send(seed);
}

void ClientProxy::initProxy(Socket &socket, int id, char type, unsigned int seed) {
    this->socket = std::move(socket);
    this->id = id;
    this->socket.send(&type, 1);
    this->socket.send(seed);
}


bool ClientProxy::isNotActive() const {
    return socket.isNotActive();
}

void ClientProxy::send(const std::shared_ptr<Message> message) const {

    if (message->getId() == this->id) return;

    char type = message->getType();
    socket.send(&type, 1);
    
    char msg_owner_id = message->getId();
    socket.send(&msg_owner_id, 1);
    
    std::string msg_str = message->getEncodedMessage();
    // unsigned short int msg_len = msg_str.length();
    // if (type == CHAT_CHAR) {
    //     unsigned short int msg_len_be = htons(msg_len);
    //     socket.send((char *) &msg_len_be, 2);
    // }
    
    socket.send(msg_str.c_str(), msg_str.size());
}

std::shared_ptr<Message> ClientProxy::recv() {
    std::shared_ptr<Message> msg_ptr;
    
    try {
        char type;
        socket.receive(&type, 1);
        msg_ptr = Protocol::CharToMessage(type, id);
        int bytesToRead = msg_ptr->getBytesToRead();
        while (bytesToRead > 0) {
            std::cout << "CLIENT PROXY READING BYTES" << bytesToRead << std::endl;
            std::vector<char> buf;
            buf.reserve(bytesToRead);
            this->socket.receive(buf.data(), bytesToRead);
            msg_ptr->decode(buf);
            bytesToRead = msg_ptr->getBytesToRead();
        }
        std::cout << "CLIENT PROXY READING BYTES" << bytesToRead << std::endl;
    } catch(const std::exception &e) {
        std::cerr << "ERROR: '"
                  << e.what() << "'" << std::endl;
    } catch(...) {
        std::cerr << "Error recv command type" << std::endl;
    }

    return msg_ptr;
}

std::string ClientProxy::getName() {
    return name;
}

int ClientProxy::getId() {
    return id;
}

int ClientProxy::get_room_id() {
    return room_id;
}