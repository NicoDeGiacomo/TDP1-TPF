#ifndef QUANTUM_CHESS_ROOMMANAGER_H
#define QUANTUM_CHESS_ROOMMANAGER_H

#include "Socket.h"
#include "Room.h"
#include <map>
#include <string>

class RoomManager: public Thread {
private:
    Socket &acceptor;
    std::map<std::string,Room> rooms;

protected:
    void run() override;

public:
    /*
     *  Constructor
     */
    RoomManager(Socket &acceptor);
    /*
     *  Constructor por copia
     */
    RoomManager(const RoomManager &other) = delete;
    /*
     *  Cierra las conexiones con los clientes y corta su ejecucion
     */
    void stop();
};


#endif //QUANTUM_CHESS_ROOMMANAGER_H
