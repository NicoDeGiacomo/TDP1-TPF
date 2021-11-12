#include "Position.h"

#include <stdexcept>

Position::Position(int x, int y) : x_(x), y_(y) {
    validate_position();
}

Position::Position(const std::string& position) :x_(0), y_(0) {
    if (position.length() > 3 || position.length() < 2) {
        throw std::invalid_argument("Invalid position.");
    }

    x_ = toascii(position[0]) - 96;
    y_ = toascii(position[1]) - 48;

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

std::string Position::getString() const {
    char position[2];
    position[0] = (char) (x_ + 96);
    position[1] = (char) (y_ + 48);

    return position;
}

bool Position::operator==(const Position &other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool Position::operator!=(const Position &other) const {
    return !(other == *this);
}
