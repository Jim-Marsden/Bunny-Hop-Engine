//
// Created by snizzfox on 5/29/20.
//

#include <iostream>
#include "movement.hpp"

void mt::movement::AddData(std::string const &String_view, const mt::movement::movementDataT &Movement_data) {
    _movement_data[String_view] = Movement_data;
}

mt::movement::movementDataT
mt::movement::GetData(std::string const &String_view) const {
    movementDataT result;
    if (_movement_data.find(String_view) != _movement_data.end()) result = _movement_data.at(String_view);
    return result;
}

float mt::movement::CalculateX() const {

    float accumulator{};
    for (auto const &[first, l_movement_data]: _movement_data) {

        if (l_movement_data.enabled)
            accumulator += l_movement_data.x;
    }

    return accumulator;
}

float mt::movement::CalculateY() const {
    float accumulator{};
    for (auto const &[first, l_movement_data]: _movement_data) {


        if (l_movement_data.enabled)
            accumulator += l_movement_data.y;
    }
    return accumulator;
}

mt::movement::movementDataT mt::movement::CalculateXandY() const {
    movementDataT accumulator{};
    for (auto const &[first, l_movement_data]: _movement_data) {
        accumulator.x += l_movement_data.x;
        accumulator.y += l_movement_data.y;
    }
    return accumulator;
}

void mt::movement::EnableValue(std::string_view const &String_view, bool State) {
    if (_movement_data.find(std::string(String_view)) != _movement_data.end()) {
        _movement_data[std::string(String_view)].enabled = State;
    } else {
        throw std::runtime_error("Element not found");
    }

}
