//
// Created by ale on 18/11/21.
//

#include "MovementCommand.h"
#include "NormalMove.h"

MovementCommand::MovementCommand(std::initializer_list <Position> positions) {
    for (auto &position : positions)
        this->_positions.push_back(position);
}
