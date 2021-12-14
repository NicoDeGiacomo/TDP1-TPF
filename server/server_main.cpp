#include <cstdio>
#include <iostream>
#include <vector>

#include "Board.h"
#include "StageMode.h"
#include <Server.h>

int main() {
    StageMode::log("STARTING SERVER");

    try {
        Server server("7777");
        server.run();
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
