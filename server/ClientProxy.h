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
    int id;
    std::string recvMessage(unsigned short int msg_len);
    unsigned short int decodeChatMessageLen();
public:
    /*
     *  Constructor
     */
    ClientProxy(Socket &socket);
    /*
     *  Constructor por copia
     */
    ClientProxy(const ClientProxy&) = delete;
    /*
     *  Asignacion por copia
     */
    ClientProxy& operator=(const ClientProxy&) = delete;
    /*
     *  Constructor por movimiento
     */
    ClientProxy(ClientProxy &&other);

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

    void setId(int id);
    
    int getId();

    bool isClosed() const;
};

#endif
