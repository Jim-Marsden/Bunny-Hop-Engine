//
// Created by james on 5/15/2020.
//

#include "drawable.hpp"

[[maybe_unused]] auto bhe::Drawable::set_texture(sf::Texture const& texture) -> bhe::returnStatus<void>
{
	sprite.setTexture(texture);
	return {};
}

auto bhe::Drawable::set_position(float top, float left) -> bhe::returnStatus<void>
{
	sprite.setPosition({top, left});
	return {};
}

bhe::Drawable::operator sf::Sprite const&() const { return sprite; }

bhe::Drawable::Drawable(const sf::Sprite& sprite_in) { sprite = sprite_in; }

auto bhe::Drawable::do_animation(std::chrono::microseconds const& time) -> bhe::returnStatus<void>
{
	if (!animation_information.empty()) {

		if (animation_information.size()>current_animation) {
			auto& frame_data = animation_information[current_animation];

			frame_data.count_next_frame(time);

			auto const x = static_cast<int>(frame_data.get_current_fame_index().value)*
					sprite.getTextureRect().width;

			sprite.setTextureRect({{static_cast<int>(x), 0},
								   {sprite.getTextureRect().height, sprite.getTextureRect().width}});

			return {};
		}
		return {false, bhe::ReturnStatusCode::OutOfRange};

	}
	return {false, bhe::ReturnStatusCode::Error};

}

auto bhe::Drawable::set_texture_rect(const sf::IntRect& rect) -> bhe::returnStatus<void>
{
	sprite.setTextureRect(rect);
	return {};

}

auto bhe::Drawable::add_animation_state(const animationState& animation_state) -> bhe::returnStatus<void>
{
	animation_information.emplace_back(animation_state);
	return {};

}

auto bhe::Drawable::set_origin(float top, float left) -> bhe::returnStatus<void>
{
	sprite.setOrigin({top, left});
	return {};

}
