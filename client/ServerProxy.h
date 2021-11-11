#ifndef _SERVER_PROXY_H_
#define _SERVER_PROXY_H_

#include "Action.h"

/*
 *  Esta clase se ocupa de hacer la traduccion de bits a Action 
 *  y viceversa
 */
class ServerProxy {
private:
    
public:
    ServerProxy();
    /*
     *  Traduce una accion a bits segun el protocolo de comunicacion 
     *  y lo envia al server.
     */
    void send(Action &action);
    /*
     *  Traduce los bits recibidos del server a una Action segun  
     *  el protocolo de comunicacio.
     */
    Action recv();
    /*
     *  Cierra la conexion con el server.
     */
    void close_connection();
};



#endif
