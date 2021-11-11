#include "doctest.h"
#include "Tests.cpp"  // NOLINT [build/c++11]

#include "BlockingQueue.h"

TEST_SUITE("Blocking Queue Tests") {
TEST_CASE("Produce and consume") {
BlockingQueue<std::string> queue;

queue.produce("value1");
CHECK_EQ(queue.top(), "value1");
}

TEST_CASE("Produce, consume and remove") {
BlockingQueue<std::string> queue;

queue.produce("value1");
queue.produce("value2");

CHECK_EQ(queue.top(), "value1");
queue.pop();
CHECK_EQ(queue.top(), "value2");
}

TEST_CASE("Multiple items") {
BlockingQueue<std::string> queue;

queue.produce("value1");
queue.produce("value2");
queue.produce("value3");
queue.produce("value4");
queue.produce("value5");
queue.produce("value6");

CHECK_EQ(queue.top(), "value1");
queue.pop();
CHECK_EQ(queue.top(), "value2");
queue.pop();
CHECK_EQ(queue.top(), "value3");
queue.pop();
CHECK_EQ(queue.top(), "value4");
queue.pop();
CHECK_EQ(queue.top(), "value5");
queue.pop();
CHECK_EQ(queue.top(), "value6");
}

TEST_CASE("Close") {
BlockingQueue<std::string> queue;

queue.produce("value1");
queue.close();

CHECK_THROWS_AS(queue.produce("value2"), ClosedQueueException);
CHECK_EQ(queue.top(), "value1");
queue.pop();
CHECK_THROWS_AS(queue.top(), ClosedQueueException);
CHECK_THROWS_AS(queue.pop(), ClosedQueueException);
}
}
