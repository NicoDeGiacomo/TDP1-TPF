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
Position Position::operator+(const Position &pos2) const {
    return {x_ + pos2.x_, y_ + pos2.y_};  // todo test que verifique que se esta validando
}
