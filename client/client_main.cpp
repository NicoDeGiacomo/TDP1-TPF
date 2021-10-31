#include <cstdio>
#include <iostream>
#include <vector>
#include "common/Socket.h"

void start_socket_and_send_2_bytes_to_test();

int main() {
    printf("STARTING CLIENT\n");
    start_socket_and_send_2_bytes_to_test();
    return 0;
}

void start_socket_and_send_2_bytes_to_test() {
    Socket socket;
    socket.connect("localhost", "7777");
    std::vector<char> buffer(2);
    buffer[0] = 'a';
    buffer[1] = 'a';
    socket.send(&buffer[0], 2);
    for (int i = 0; i<2 ; i++){
        std::cout << buffer[i] << std::endl;
    }
    do {
        // para q no se vaya del stack y muera el socket antes q reciva el otro
        std::cout << '\n' << "Press enter to continue...";
    } while (std::cin.get() != '\n');
}
