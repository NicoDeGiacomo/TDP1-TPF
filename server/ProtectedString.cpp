//
// Created by ale on 9/11/2021.
//

#include "ProtectedString.h"
#include <utility>
#include <iostream>

ProtectedString::ProtectedString() {
}

ProtectedString::ProtectedString(ProtectedString &&other) {
    this->strings = std::move(other.strings);
}

ProtectedString &ProtectedString::operator=(ProtectedString &&other) {
    this->strings = std::move(other.strings);
    return *this;
}

ProtectedString::~ProtectedString(){}

void ProtectedString::addString(std::string&& string){
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    this->strings.push(std::move(string));
    this->conditionVariable.notify_all();
}

void ProtectedString::getStringIfNotEmpty(std::string& string){
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->strings.empty()) {
        this->conditionVariable.wait(uniqueLock);
    }
    string = std::move(this->strings.front());
    this->strings.pop();
}