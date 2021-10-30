#include "Position.h"

#include <stdexcept>

Position::Position(unsigned short x, unsigned short y) : x_(x), y_(y) {
    validate_position();
}

void Position::validate_position() const {
    if (x_ > 8 || y_ > 8 || x_ < 1 || y_ < 1) {
        throw std::invalid_argument("Invalid position.");
    }
}
