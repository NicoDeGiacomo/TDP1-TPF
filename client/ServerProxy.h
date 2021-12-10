#ifndef _SERVER_PROXY_H_
#define _SERVER_PROXY_H_

#include "Socket.h"
#include "Message.h"

/*
 *  Esta clase se ocupa de hacer la traduccion de bits a Message 
 *  y viceversa
 */
class ServerProxy {
private:
    Socket socket;
    std::string host;
    std::string service;
    unsigned int seed;
    
public:
    ServerProxy(const char *host, const char *service);

    void connect();
    /*
     *  Traduce una accion a bits segun el protocolo de comunicacion 
     *  y lo envia al server.
     */
    void send(const std::shared_ptr<Message> message);
    /*
     *  Traduce los bits recibidos del server a una Message segun  
     *  el protocolo de comunicacio.
     */
    std::shared_ptr<Message> recv();
    /*
     *  Cierra la conexion con el server.
     */
    void close_connection();

    unsigned int getSeed();
};



#endif
