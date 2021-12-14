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
        StageMode::log(
                    std::string("Exception caught in server: '") + e.what()
                        + "'");
        return 1;
    } catch(...) {
        StageMode::log("Unknown error caught in server.");
        return 1;
    }
    return 0;
}
