#include <cstdio>
#include <iostream>
#include <vector>

#include "Board.h"
#include "RoomManager.h"

int main() {
    printf("STARTING SERVER\n");

    // if (argc != 3) {
    //     std::cerr << "Error en la cantidad de argumentos\n"
    //     << "El servidor se ejecuta de la siguiente manera:\n"
    //     << "./server <service>\n";
    //     return 1;
    // }

    try {
        RoomManager roomManager;
        roomManager.start();
        
    } catch(const std::exception &e) {
        std::cerr << "Se atrapó una excepcion en el servidor: '" 
                  << e.what() << "'" << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Error desconocido en el servidor" << std::endl;
        return 2;
    }
    return 0;
}
