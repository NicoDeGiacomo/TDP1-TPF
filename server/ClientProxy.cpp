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


/***********************
    Metodos privados
************************/

unsigned short int ClientProxy::decodeChatMessageLen() {
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

/***********************
    Metodos publicos
************************/

ClientProxy::ClientProxy(Socket &socket) : socket(std::move(socket)), id(-1) {}

ClientProxy::ClientProxy(Socket &socket, int id, char type, unsigned int seed)
                        : socket(std::move(socket)), id(id) {
    // this->socket.send(&type, 1);
    // this->socket.send(seed);
    seed++;
    type++;
}

ClientProxy::ClientProxy(ClientProxy &&other) 
                : socket(std::move(other.socket)), id(other.id) {}

void ClientProxy::send(const std::shared_ptr<Message> message) const {

    if (this->socket.isNotActive()) return;
    if (message->getId() == this->id) return;

    char type = message->getType();
    socket.send(&type, 1);
    
    char msg_owner_id = message->getId();
    socket.send(&msg_owner_id, 1);
    
    std::string msg_str = message->getEncodedMessage();
    socket.send(msg_str.c_str(), msg_str.size());
}

std::shared_ptr<Message> ClientProxy::recv() {
    std::shared_ptr<Message> msg_ptr;
    
    char type;
    socket.receive(&type, 1);
    msg_ptr = Protocol::CharToMessage(type, id);
    int bytesToRead = msg_ptr->getBytesToRead();
    while (bytesToRead > 0) {
        std::vector<char> buf;
        buf.reserve(bytesToRead);
        this->socket.receive(buf.data(), bytesToRead);
        msg_ptr->decode(buf);
        bytesToRead = msg_ptr->getBytesToRead();
    }

    return msg_ptr;
}

void ClientProxy::setId(int id) {
    this->id = id;
}

int ClientProxy::getId() {
    return id;
}

void ClientProxy::close_connection() {
    this->socket.shutdown();
}

bool ClientProxy::isClosed() const {
    return this->socket.isNotActive();
}
