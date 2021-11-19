#include "ServerProxy.h"
#include "Protocol.h"
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
    return Protocol::StringToMessage(msg_str, msg_owner_id);
}


void encodeChatMessage(std::shared_ptr<Message>) {

}

/***********************
    Metodos publicos
************************/

ServerProxy::ServerProxy() : id(-1) {}

void ServerProxy::connect(const char *host, const char *service) {
    socket.connect(host, service);
    // Justo despues de conectarse podria recibir el id que le corresponde
}

void ServerProxy::send(const std::shared_ptr<Message> message) {
    // TODO: Agregar funcionalidad para que no envie solo mensajes de chat
    std::string msg_str = Protocol::MessageToString(message);
    char type = CHAT_CHAR;
    unsigned short int msg_len = msg_str.length();
    unsigned short int msg_len_be = htons(msg_len);
    
    socket.send(&type, 1);
    socket.send((char *) &msg_len_be, 2);
    socket.send(msg_str.c_str(), msg_len);
}

std::shared_ptr<Message> ServerProxy::recv() {
    std::shared_ptr<Message> msg_ptr;

    char type;
    socket.receive(&type, 1);

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

void ServerProxy::close_connection() {

}