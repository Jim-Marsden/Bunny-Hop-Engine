//
// Created by snizzfox on 5/29/20.
//

#include "movement.hpp"

void mt::movement::AddData(const std::string_view &String_view, const mt::movement::movementDataT &Movement_data) {
    movement_data[String_view] = Movement_data;
}

mt::movement::movementDataT
mt::movement::GetData(const std::string_view &String_view) const {
    movementDataT result;
    if (movement_data.find(String_view) != movement_data.end()) result = movement_data.at(String_view);
    return result;
}

float mt::movement::CalculateX() const {

    float accumulator{};
    for (auto const &[first, l_movement_data]: movement_data) {
        accumulator += l_movement_data.x;
    }
    return accumulator;
}

float mt::movement::CalculateY() const {
    float accumulator{};
    for (auto const &[first, l_movement_data]: movement_data) {
        accumulator += l_movement_data.y;
    }
    return accumulator;
}

mt::movement::movementDataT mt::movement::CalculateXandY() const {
    movementDataT accumulator{};
    for (auto const &[first, l_movement_data]: movement_data) {
        accumulator.x += l_movement_data.x;
        accumulator.y += l_movement_data.y;
    }
    return accumulator;
}
