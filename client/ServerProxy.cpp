#include "ServerProxy.h"
#include "Protocol.h"
#include "ChatMessage.h"
#include "NormalMoveMessage.h"
#include "SplitMoveMessage.h"
#include "MergeMoveMessage.h"
#include "SelectMessage.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#define CHAT_CHAR 'c'
#define NORMAL_MOVE_CHAR 'n'
#define SPLIT_MOVE_CHAR 's'
#define MERGE_MOVE_CHAR 'm'

/***********************
    Metodos privados
************************/

std::shared_ptr<Message> ServerProxy::decodeChatMessage() {
    std::cout << "Decoding chat msg\n";
    char msg_owner_id;
    socket.receive(&msg_owner_id, 1);
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
    std::cout << "Finish Decoding chat msg\n";
    return std::make_shared<ChatMessage>(msg_str, msg_owner_id);
}


unsigned short int ServerProxy::decodeChatMessageLen() {
    std::cout << "start decoding chat message" << std::endl;
    char _msg_len[2];
    socket.receive(_msg_len, 2);
    unsigned short int name_len_be;
    memcpy(&name_len_be, _msg_len, 2);
    unsigned short int msg_len = ntohs(name_len_be);
    return msg_len;
}

std::string ServerProxy::recvMessage(unsigned short int msg_len) {
    std::vector<char> msg;
    msg.reserve(msg_len);
    char *buf = &msg[0];
    socket.receive(buf, msg_len);
    std::string msg_str(buf, msg_len);
    return msg_str;
}

/***********************
    Metodos publicos
************************/

ServerProxy::ServerProxy(const char *host, const char *service) : id(-1) {
    connect(host, service);
}

void ServerProxy::connect(const char *host, const char *service) {
    socket.connect(host, service);
    // Justo despues de conectarse podria recibir el id que le corresponde
    socket.receive(&playerType, 1);
}

void ServerProxy::send(const std::shared_ptr<Message> message) {
    std::string msg_str = Protocol::MessageToString(message);
    char type = message->getType();
    socket.send(&type, 1);
    
    if (type == CHAT_CHAR) {
        unsigned short int msg_len = msg_str.length();
        unsigned short int msg_len_be = htons(msg_len);
        socket.send((char *) &msg_len_be, 2);
    }
    socket.send(msg_str.c_str(), msg_str.size());    
}

std::shared_ptr<Message> ServerProxy::recv() {
    char type;
    socket.receive(&type, 1);
    char msg_owner_id;
    socket.receive(&msg_owner_id, 1);
    
    std::shared_ptr<Message> msg_ptr;
    std::string msg_str;
    unsigned short int msg_len;

    switch (type) {
    case CHAT_CHAR:
        std::cout << "about to decode chat message" << std::endl;
        msg_len = decodeChatMessageLen();
        msg_str = recvMessage(msg_len);
        msg_ptr = std::make_shared<ChatMessage>(msg_str, msg_owner_id);
        break;
    case NORMAL_MOVE_CHAR:
        msg_str = recvMessage(4);
        msg_ptr = std::make_shared<NormalMoveMessage>(msg_str, msg_owner_id);
        break;
    case SPLIT_MOVE_CHAR:
        msg_str = recvMessage(6);
        msg_ptr = std::make_shared<SplitMoveMessage>(msg_str, msg_owner_id);
        break;
    case MERGE_MOVE_CHAR:
        msg_str = recvMessage(6);
        msg_ptr = std::make_shared<MergeMoveMessage>(msg_str, msg_owner_id);
        break;
    default:
        throw std::runtime_error("Unknown command");
        break;
    }
    return msg_ptr;
}

void ServerProxy::close_connection() {
    this->socket.shutdown();
}

char ServerProxy::getPlayerType() {
    return playerType;
}
