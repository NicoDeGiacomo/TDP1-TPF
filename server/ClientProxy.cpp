#include "ClientProxy.h"
#include "Socket.h"
#include "Message.h"
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

std::shared_ptr<Message> ClientProxy::decodeChatMessage() {
    char _msg_len[2];
    socket.receive(_msg_len, 2);
    unsigned short int name_len_be;
    memcpy(&name_len_be, _msg_len, 2);
    unsigned short int msg_len = ntohs(name_len_be);
    std::vector<char> msg;
    msg.reserve(msg_len);
    char *buf = &msg[0];
    socket.receive(buf, msg_len);
    std::string msg_str(buf, msg_len);
    return Protocol::StringToMessage(msg_str, id);
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

    // TODO: Agregar funcionalidad para que no envie solo mensajes de chat
    std::string msg_str = Protocol::MessageToString(message);
    char type = CHAT_CHAR;
    unsigned short int msg_len = msg_str.length();
    unsigned short int msg_len_be = htons(msg_len);
    char msg_owner_id = message->getId();
    
    socket.send(&type, 1);
    socket.send(&msg_owner_id, 1);
    socket.send((char *) &msg_len_be, 2);
    socket.send(msg_str.c_str(), msg_len);
}

std::shared_ptr<Message> ClientProxy::recv() {
    std::shared_ptr<Message> msg_ptr;

    char type;
    try {
        socket.receive(&type, 1);
    } catch(const std::exception &e) {
        std::cerr << "ERROR: '"
                  << e.what() << "'" << std::endl;
    } catch(...) {
        std::cerr << "Error recv command type" << std::endl;
    }

    switch (type) {
    case CHAT_CHAR:
        msg_ptr = decodeChatMessage();
        break;
    case NORMAL_MOVE_CHAR:
        throw std::runtime_error("Move message not supported yet");
        break;
    case SPLIT_MOVE_CHAR:
        throw std::runtime_error("Move message not supported yet");
        break;
    case MERGE_MOVE_CHAR:
        throw std::runtime_error("Move message not supported yet");
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