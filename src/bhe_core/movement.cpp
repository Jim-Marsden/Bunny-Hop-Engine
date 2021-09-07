//
// Created by snizzfox on 5/29/20.
//

#include <iostream>
#include "movement.hpp"

void bhe::Movement::add_data(std::string const& string_view, const bhe::Movement::movementDataT& movement_data_in)
{
	movement_data[string_view] = movement_data_in;
}

bhe::Movement::movementDataT
bhe::Movement::get_data(std::string const& string_view) const
{
	movementDataT result;
	if (movement_data.find(string_view)!=movement_data.end()) result = movement_data.at(string_view);
	return result;
}

float bhe::Movement::calculate_x()
{

	float accumulator{};
	for (auto &[first, l_movement_data]: movement_data) {

		if (l_movement_data.enabled) {
			if (l_movement_data.timer>0 || !l_movement_data.enabled_timer) {
				accumulator += l_movement_data.x;
				--l_movement_data.timer;
			}
		}
	}

	return accumulator;
}

float bhe::Movement::calculate_y()
{
	float accumulator{};

	for (auto  &[first, l_movement_data]: movement_data) {

		if (l_movement_data.enabled_timer && l_movement_data.enabled) {
			if (l_movement_data.timer>=0) {
				accumulator += l_movement_data.y;
				--l_movement_data.timer;
			}

		}
		else if (l_movement_data.enabled) {
			accumulator += l_movement_data.y;
		}

	}
	return accumulator;
}

bhe::Movement::movementDataT bhe::Movement::calculate_x_and_y()
{
	movementDataT accumulator{};
	for (auto const &[first, l_movement_data]: movement_data) {
		accumulator.x += l_movement_data.x;
		accumulator.y += l_movement_data.y;
	}
	return accumulator;
}

void bhe::Movement::enable_value(std::string_view const& string_view, bool state)
{
	if (movement_data.find(std::string(string_view))!=movement_data.end()) {
		movement_data[std::string(string_view)].enabled = state;
	}
	else {
		throw std::runtime_error("Element not found");
	}

}

void bhe::Movement::reset_timer(std::string_view const& value)
{
	if (movement_data.find(std::string(value))!=movement_data.end()) {
		movement_data[std::string(value)].timer = movement_data[std::string(value)].max_timer;
	}
	else {
		throw std::runtime_error("Element not found");
	}

}


