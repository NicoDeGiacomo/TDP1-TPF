#include <cstdio>
#include <iostream>
#include <vector>

#include "Board.h"
#include "RoomManager.h"

int main() {
    printf("STARTING SERVER\n");
    RoomManager roomManager;
    roomManager.start();
    return 0;
}
