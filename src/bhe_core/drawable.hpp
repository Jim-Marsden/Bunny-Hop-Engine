//
// Created by james on 5/15/2020.
//

#pragma once

#include "bhe_core/animationState.hpp"
#include "bhe_core/Return_Status.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>

namespace bhe {
class Drawable {

protected:
	sf::Sprite sprite;
	//float current_frame_time_{0.0F};

	std::vector<animationState> animation_information{};
	std::size_t current_animation{0};

public:
	Drawable() = default;

	Drawable(Drawable const&) = default;

	Drawable(Drawable&&) = default;

	~Drawable() = default;

	Drawable& operator=(Drawable&&) = default;

	Drawable& operator=(Drawable const&) = default;
	explicit operator sf::Sprite const&() const;

	explicit Drawable(sf::Sprite const& sprite);

	[[maybe_unused]] auto set_texture(sf::Texture const& texture) -> bhe::returnStatus<void>;

	auto set_position(float top, float left) -> returnStatus<void>;

	auto set_origin(float top, float left) -> returnStatus<void>;

	auto set_texture_rect(sf::IntRect const& rect) -> returnStatus<void>;

	auto do_animation(std::chrono::microseconds const& time) -> returnStatus<void>;

	auto add_animation_state(animationState const& animation_state) -> returnStatus<void>;
};

} // namespace bhe
