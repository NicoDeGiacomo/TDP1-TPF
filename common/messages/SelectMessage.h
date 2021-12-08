//
// Created by ale on 16/11/21.
//

#ifndef QUANTUM_CHESS_SELECTMESSAGE_H
#define QUANTUM_CHESS_SELECTMESSAGE_H

#include "Message.h"

class SelectMessage : public Message {
public:
    SelectMessage(int id = -1);
    const std::string getMessage() const override;
    virtual void apply(Board& board, 
                    BlockingQueue<std::shared_ptr<std::string>>&) const override;
    // const std::string& getId() const override;
};


#endif //QUANTUM_CHESS_SELECTMESSAGE_H
