#ifndef QUANTUM_CHESS_MOVEMENTCOMMAND_H
#define QUANTUM_CHESS_MOVEMENTCOMMAND_H

#include <vector>
#include <Position.h>
#include <Board.h>

class MovementCommand {
protected:
    std::vector<Position> _positions;
public:
    explicit MovementCommand(std::initializer_list<Position> positions);
    virtual void move(Board&) {};
    virtual ~MovementCommand() = default;
};


#endif //QUANTUM_CHESS_MOVEMENTCOMMAND_H
