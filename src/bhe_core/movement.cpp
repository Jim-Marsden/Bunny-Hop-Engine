//
// Created by snizzfox on 5/29/20.
//

#include <iostream>
#include "movement.hpp"

void bhe::movement::AddData(std::string const &String_View, const bhe::movement::movementDataT &Movement_Data) {
  movement_data_[String_View] = Movement_Data;
}

bhe::movement::movementDataT
bhe::movement::GetData(std::string const &String_View) const {
    movementDataT result;
    if (movement_data_.find(String_View) != movement_data_.end()) result = movement_data_.at(String_View);
    return result;
}


float bhe::movement::CalculateX() {

    float accumulator{};
    for (auto &[first, l_movement_data]: movement_data_) {

        if (l_movement_data.enabled) {
            if (l_movement_data.timer > 0 || !l_movement_data.enabled_timer) {
                accumulator += l_movement_data.x;
                --l_movement_data.timer;
            }
        }
    }

    return accumulator;
}

float bhe::movement::CalculateY() {
    float accumulator{};

    for (auto  &[first, l_movement_data]: movement_data_) {


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

bhe::movement::movementDataT bhe::movement::CalculateXandY() {
    movementDataT accumulator{};
    for (auto const &[first, l_movement_data]: movement_data_) {
        accumulator.x += l_movement_data.x;
        accumulator.y += l_movement_data.y;
    }
    return accumulator;
}

void bhe::movement::EnableValue(std::string_view const &String_View, bool State) {
    if (movement_data_.find(std::string(String_View)) != movement_data_.end()) {
      movement_data_[std::string(String_View)].enabled = State;
    } else {
        throw std::runtime_error("Element not found");
    }

}

void bhe::movement::ResetTimer(std::string_view const &Value) {
    if (movement_data_.find(std::string(Value)) != movement_data_.end()) {
      movement_data_[std::string(Value)].timer = movement_data_[std::string(Value)].max_timer;
    } else {
        throw std::runtime_error("Element not found");
    }

}


