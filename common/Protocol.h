#ifndef QUANTUM_CHESS_PROTOCOL_H
#define QUANTUM_CHESS_PROTOCOL_H

#include <string>
#include <messages/Message.h>
#include <memory>

#define CHAT_CHAR 'c'
#define NORMAL_MOVE_CHAR 'n'
#define SPLIT_MOVE_CHAR 's'
#define MERGE_MOVE_CHAR 'm'
#define WHITE_CHAR 'W'
#define BLACK_CHAR 'B'
#define SPECTATOR_CHAR 'O'
#define PLAYER_NAME_CHAR 'p'
#define ROOM_ID_CHAR 'r'
#define PLAYER_TYPE_CHAR 't'
#define SEED_CHAR 'S'

namespace Protocol {
    std::string MessageToString(const std::shared_ptr<Message>& message);
    std::shared_ptr<Message> CharToMessage(char type);
    std::shared_ptr<Message> CharToMessage(char type, int id);
}
#endif //QUANTUM_CHESS_PROTOCOL_H
