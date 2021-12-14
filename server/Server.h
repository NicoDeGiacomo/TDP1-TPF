#ifndef SERVER_H
#define SERVER_H

#include <Socket.h>

class Server {
private:
    std::string service;
public:
    /*
     *  Constructor
     */
    explicit Server(const std::string service);
    /*
     *  Lanza el hilo con el RoomManager y se queda leyendo de entrada estandar.
     *  Una vez que lee el caracter 'q', detiene la ejecucion del hilo
     *  RoomManager y cierra el servidor.
     */
    void run();
};





#endif
