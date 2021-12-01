#ifndef _CLIENT_PROXY_H_
#define _CLIENT_PROXY_H_

#include "Socket.h"
#include "Message.h"

/*
 *  Esta clase se ocupa de hacer la traduccion de bits a Message 
 *  y viceversa
 */
class ClientProxy {
private:
    Socket socket;
    bool is_player;
    int room_id;
    std::string name;
    int id;
    std::string recvMessage(unsigned short int msg_len);
    unsigned short int decodeChatMessageLen();
public:
    ClientProxy();

    ClientProxy(Socket &socket, int id, char type, unsigned int seed);

    void initProxy(Socket &socket, int id, char type, unsigned int seed);

    bool isNotActive() const;
    /*
     *  Traduce una accion a bits segun el protocolo de comunicacion 
     *  y lo envia al cliente.
     */
    void send(const std::shared_ptr<Message> message) const;
    /*
     *  Traduce los bits recibidos del cliente a un Message segun  
     *  el protocolo de comunicacion.
     */
    std::shared_ptr<Message> recv();
    /*
     *  Cierra la conexion con el cliente.
     */
    void close_connection();

    void initialize();

    int getId();

    std::string getName();

    int get_room_id();
};

#endif
