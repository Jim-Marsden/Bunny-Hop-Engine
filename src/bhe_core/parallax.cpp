//
// Created by james on 5/15/2020.
//

#include "parallax.hpp"

bhe::Parallax::Parallax(const sf::Texture& texture, float offset_in) : sprite(texture), offset(offset_in){}

sf::Sprite const& bhe::Parallax::get_sprite() const
{
	return sprite;
}

void bhe::Parallax::apply_parallax(const sf::Vector2f& player_speed)
{

	sprite.setPosition({player_speed.x/offset,
						player_speed.y/offset});
	//TODO stuff

}

bhe::Parallax::operator sf::Sprite const&() const
{
	return sprite;
}

bhe::Parallax::operator sf::Drawable const*() const
{
	return &sprite;
}

