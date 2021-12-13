#include <Chat.h>
#include <StageMode.h>

Chat::Chat() {}

BlockingQueue<std::shared_ptr<std::string>>& Chat::getQueue() {
    return this->queue;
}

void Chat::addMessage(int user_id, const std::string &message) {
    std::string msg;
    
    if (user_id == -1) msg = "You: ";
    else msg = this->users[user_id] + ": ";

    msg += message;

    StageMode::log(std::string("[CHAT] ") + msg);
    queue.produce(std::make_shared<std::string>(msg));
}

void Chat::addUser(int user_id, std::string name) {
    this->users[user_id] = name;
}

std::string Chat::getName(int id) {
    return this->users[id];
}
