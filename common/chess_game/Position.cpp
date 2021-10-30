#include "Position.h"

#include <stdexcept>

Position::Position(int x, int y) : x_(x), y_(y) {
    validate_position();
}

void Position::validate_position() const {
    if (x_ > 8 || y_ > 8 || x_ < 1 || y_ < 1) {
        throw std::invalid_argument("Invalid position.");
    }
}

int Position::getX() const {
    return x_;
}

int Position::getY() const {
    return y_;
}

bool Position::operator==(const Position &other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool Position::operator!=(const Position &other) const {
    return !(other == *this);
}
