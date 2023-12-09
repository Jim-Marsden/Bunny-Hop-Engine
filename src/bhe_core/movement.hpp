//
// Created by snizzfox on 5/29/20.
//

#pragma once

#include <string_view>
#include <map>

namespace bhe {
class Movement {

public:

	struct movementDataT {
		//std::string_view get_name;
		bool enabled{};
		float x{}, y{};
		bool enabled_timer{};
		int timer{};
		int max_timer{};
		//movementDataT() = default;


	};

protected:
	std::map<std::string, movementDataT> movement_data;
public:
	void add_data(std::string const& string_view, movementDataT const& movement_data);

	void enable_value(std::string_view const& string_view, bool state);

	[[nodiscard]] movementDataT get_data(std::string const& string_view) const;

	[[nodiscard]] float calculate_x();

	[[nodiscard]] float calculate_y();

	[[nodiscard]] movementDataT calculate_x_and_y();

	void reset_timer(std::string_view const& value);

};
} //namespace bhe
