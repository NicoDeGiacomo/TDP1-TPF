#include "tests/doctest/doctest.h"
#include "Tests.cpp"

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
}
