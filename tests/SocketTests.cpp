#include "doctest.h"
#include "Tests.cpp"  // NOLINT [build/c++11]

#include <Socket.h>

TEST_SUITE("Socket tests") {
TEST_CASE("Send and receive") {
    Socket acceptor;
    acceptor.bind("7777");
    acceptor.listen(1);

    Socket client;
    client.connect("localhost", "7777");

    char send[3] = "hi";
    client.send(send, 2);

    Socket peer = acceptor.accept();
    char read[2];
    peer.receive(read, 2);

    CHECK_EQ(read[0], 'h');
    CHECK_EQ(read[1], 'i');
}

TEST_CASE("Error") {
    Socket client;
    CHECK_THROWS_WITH_AS(client.connect(".", "."),
                         "Failed getting address information.",
                         SocketException);
    CHECK_THROWS_WITH_AS(client.connect("localhost", "7777"),
                         "Error connecting to server.",
                         SocketException);
}

TEST_CASE("Error description") {
    Socket client;
    try {
        client.connect(".", ".");
    } catch (SocketException &e) {
        std::string error = e.what();
        CHECK_EQ(error, "Failed getting address information.");
    }
    try {
        client.connect("localhost", "7777");
    } catch (SocketException &e) {
        std::string error = e.what();
        CHECK_EQ(error, "Error connecting to server.");
    }
}
}
