#include "MeasurementNotation.h"

MeasurementNotation::MeasurementNotation(bool result) : result_(result) {}

std::string MeasurementNotation::getString() {
    if (result_) {
        return "*";
    }

    return "#";
}
std::shared_ptr<Message> MeasurementNotation::getMoveMessage() {
    return nullptr;
}
