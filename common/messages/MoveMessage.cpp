//
// Created by ale on 16/11/21.
//

#include "MoveMessage.h"
#include "movements/MovementCommand.h"
#include <iostream>
#include <NormalMove.h>
#include <SplitMove.h>
#include <MergeMove.h>

//TODO: here i should decode the message
const std::string MoveMessage::getMessage() const {
    std::cout << "get message from MoveMessage class" << std::endl;
    return this->_message;
}

// const std::string &MoveMessage::getId() const {
//     std::cout << "get id from MoveMessage class" << std::endl;
//     return Message::getId();
// }

//TODO: here i should encode the message
MoveMessage::MoveMessage(const std::string &message, int id) : Message(message, id) {
    std::cout << "constructor of MoveMessage class" << std::endl;
    this->movement.reset();
    // if (message.at(1) == NORMAL_MOVE){
    //     Position from(this->charToInt(message.at(2)),
    //                   this->charToInt(message.at(3)));
    //     Position to(this->charToInt(message.at(4)),
    //                 this->charToInt(message.at(5)));
    //     this->movement = std::make_unique<NormalMove>(std::move(from),
    //                                                   std::move(to));
    // } else if (message.at(1) == MERGE_MOVE){

    //     Position from1(this->charToInt(message.at(2)),
    //                   this->charToInt(message.at(3)));
    //     Position from2(this->charToInt(message.at(4)),
    //                 this->charToInt(message.at(5)));
    //     Position to(this->charToInt(message.at(6)),
    //                    this->charToInt(message.at(7)));
    //     this->movement = std::make_unique<MergeMove>(std::move(from1),
    //                                                  std::move(from2),
    //                                                  std::move(to));
    // } else if (message.at(1) == SPLIT_MOVE){

    //     Position from(this->charToInt(message.at(2)),
    //                   this->charToInt(message.at(3)));
    //     Position to1(this->charToInt(message.at(4)),
    //                 this->charToInt(message.at(5)));
    //     Position to2(this->charToInt(message.at(6)),
    //                  this->charToInt(message.at(7)));
    //     this->movement = std::make_unique<SplitMove>(std::move(from),
    //                                                  std::move(to1),
    //                                                  std::move(to2));
    // } else {
    //     //no such type of move :(
    //     Position from(this->charToInt(message.at(2)),
    //                   this->charToInt(message.at(3)));
    //     Position to(this->charToInt(message.at(4)),
    //                 this->charToInt(message.at(5)));
    //     this->movement = std::make_unique<NormalMove>(std::move(from),
    //                                                   std::move(to));
    // }
}

int MoveMessage::charToInt(const char &i) {
    return i - '0';
}

void MoveMessage::apply(Board &board) const {
    std::cout << "apply move message" << std::endl;
    this->movement->move(board);
}
