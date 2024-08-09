//
// Created by james on 5/15/2020.
//

#pragma once

#include "animationState.hpp"
#include "Return_Status.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>

#include "delta_time.hpp"

namespace bhe {
class Drawable {

protected:
	sf::Sprite sprite;
	//float current_frame_time_{0.0F};

	std::vector<animationState> animation_information{};
	std::size_t current_animation{0};

public:
	Drawable() = delete;

	Drawable(Drawable const&) = default;

	Drawable(Drawable&&) = default;

	~Drawable() = default;

	Drawable& operator=(Drawable&&) = default;

	Drawable& operator=(Drawable const&) = default;
	explicit operator sf::Sprite const&() const;

	explicit Drawable(sf::Sprite const& sprite);

	explicit Drawable(sf::Texture const &texture);

	// TODO remove all the returnStatus<void>

	[[maybe_unused]] auto set_texture(sf::Texture const& texture) -> bhe::returnStatus<void>;

	auto set_position(float top, float left) -> returnStatus<void>;

	auto set_origin(float top, float left) -> returnStatus<void>;

	auto set_texture_rect(sf::IntRect const& rect) -> returnStatus<void>;

	auto do_animation(std::chrono::microseconds const& time) -> returnStatus<void>;

	auto do_animation(delta_time const& time) -> returnStatus<void>;

	auto add_animation_state(animationState const& animation_state) -> returnStatus<void>;


};

} // namespace bhe
