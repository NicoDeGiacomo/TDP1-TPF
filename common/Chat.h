#ifndef CHAT_H
#define CHAT_H

#include <map>
#include <string>
#include <BlockingQueue.h>

class Chat {
private:
    BlockingQueue<std::shared_ptr<std::string>> queue;
    std::map<int, std::string> users;

public:
    Chat();
    BlockingQueue<std::shared_ptr<std::string>>& getQueue();
    void addMessage(int user_id, const std::string &message);
    void addUser(int user_id, std::string name);
    std::string getName(int id);
};

#endif // CHAT_H
