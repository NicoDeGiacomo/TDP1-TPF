//
// Created by ale on 9/11/2021.
//

#ifndef QUANTUM_CHESS_PROTECTEDSTRING_H
#define QUANTUM_CHESS_PROTECTEDSTRING_H

#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

class ProtectedString {
private:
    std::queue<std::string> strings;
    std::mutex mutex;
    std::condition_variable conditionVariable;

public:
    /* Initializes imClosed as false */
    ProtectedString();
    ProtectedString(const ProtectedString &) = delete;
    ProtectedString &operator=(const ProtectedString &) = delete;
    ProtectedString(ProtectedString &&other);
    ProtectedString &operator=(ProtectedString &&other);
    ~ProtectedString();
    /* Thread safe. addString a string into the queue */
    void addString(std::string&& string);
    /* Blocking, thread safe. pop a string off of the queue */
    void getStringIfNotEmpty(std::string& string);
};


#endif //QUANTUM_CHESS_PROTECTEDSTRING_H
