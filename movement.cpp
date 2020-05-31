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


float mt::movement::CalculateX() {

    float accumulator{};
    for (auto &[first, l_movement_data]: _movement_data) {

        if (l_movement_data.enabled) {
            if (l_movement_data.timer > 0 || !l_movement_data.enabled_timer) {
                accumulator += l_movement_data.x;
                --l_movement_data.timer;
            }
        }
    }

    return accumulator;
}

float mt::movement::CalculateY() {
    float accumulator{};

    auto is_valid_test = [](movementDataT Element) -> bool {
        return (Element.timer > 0 && Element.enabled_timer);
    };
    for (auto  &[first, l_movement_data]: _movement_data) {


        if (l_movement_data.enabled_timer && l_movement_data.enabled) {
            if (l_movement_data.timer >= 0) {
                accumulator += l_movement_data.y;
                --l_movement_data.timer;
            }


        } else if (l_movement_data.enabled) {
            accumulator += l_movement_data.y;
        }


    }
    return accumulator;
}

mt::movement::movementDataT mt::movement::CalculateXandY() {
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

void mt::movement::ResetTimer(std::string_view const &Value) {
    if (_movement_data.find(std::string(Value)) != _movement_data.end()) {
        _movement_data[std::string(Value)].timer = _movement_data[std::string(Value)].max_timer;
    } else {
        throw std::runtime_error("Element not found");
    }

}


