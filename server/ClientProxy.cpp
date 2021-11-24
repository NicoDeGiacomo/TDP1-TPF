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


#define CHAT_CHAR 'c'
#define NORMAL_MOVE_CHAR 'n'
#define SPLIT_MOVE_CHAR 's'
#define MERGE_MOVE_CHAR 'm'

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

ClientProxy::ClientProxy(Socket &socket, int id) 
                        : socket(std::move(socket)), is_player(false), id(id) {}

void ClientProxy::initProxy(Socket &socket, int id) {
    this->socket = std::move(socket);
    this->id = id;
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
    
    std::string msg_str = Protocol::MessageToString(message);
    unsigned short int msg_len = msg_str.length();
    if (type == CHAT_CHAR) {
        unsigned short int msg_len_be = htons(msg_len);
        socket.send((char *) &msg_len_be, 2);
    }
    
    socket.send(msg_str.c_str(), msg_len);
}

std::shared_ptr<Message> ClientProxy::recv() {
    char type;
    try {
        socket.receive(&type, 1);
    } catch(const std::exception &e) {
        std::cerr << "ERROR: '"
                  << e.what() << "'" << std::endl;
    } catch(...) {
        std::cerr << "Error recv command type" << std::endl;
    }

    std::shared_ptr<Message> msg_ptr;
    std::string msg_str;
    unsigned short int msg_len;
    switch (type) {
    case CHAT_CHAR:
        std::cout << "about to decode chat message" << std::endl;
        msg_len = decodeChatMessageLen();
        msg_str = recvMessage(msg_len);
        msg_ptr = std::make_shared<ChatMessage>(msg_str, id);
        break;
    case NORMAL_MOVE_CHAR:
        msg_str = recvMessage(4);
        msg_ptr = std::make_shared<NormalMoveMessage>(msg_str, id);
        break;
    case SPLIT_MOVE_CHAR:
        msg_str = recvMessage(6);
        msg_ptr = std::make_shared<SplitMoveMessage>(msg_str, id);
        break;
    case MERGE_MOVE_CHAR:
        msg_str = recvMessage(6);
        msg_ptr = std::make_shared<MergeMoveMessage>(msg_str, id);
        break;
    default:
        throw std::runtime_error("Unknown command");
        break;
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