#include "ServerProxy.h"
#include "Protocol.h"
#include "ChatMessage.h"
#include "NormalMoveMessage.h"
#include "SplitMoveMessage.h"
#include "MergeMoveMessage.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

/***********************
    Metodos publicos
************************/

ServerProxy::ServerProxy(const char *host, const char *service) 
                        : host(host), service(service) {}

void ServerProxy::connect() {
    socket.connect(host.c_str(), service.c_str());
}

void ServerProxy::send(const std::shared_ptr<Message> message) {
    char type = message->getType();
    socket.send(&type, 1);
    std::string msg_str = message->getEncodedMessage();
    socket.send(msg_str.c_str(), msg_str.size());    
}

std::shared_ptr<Message> ServerProxy::recv() {
    std::shared_ptr<Message> msg_ptr;

    char type;
    char msg_owner_id;
    socket.receive(&type, 1);
    socket.receive(&msg_owner_id, 1);
    msg_ptr = Protocol::CharToMessage(type, msg_owner_id);
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

void ServerProxy::close_connection() {
    this->socket.shutdown();
}

unsigned int ServerProxy::getSeed() {
    return seed;
}
