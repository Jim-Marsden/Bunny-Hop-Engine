//
// Created by james on 5/15/2020.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <type_traits>

namespace bhe {
template<class Sprite_Type>
void do_draw(Sprite_Type const& drawable, sf::RenderWindow& window)
{
	window.draw(static_cast<sf::Sprite>(drawable));
}

template<>
void do_draw<sf::RectangleShape>(sf::RectangleShape const& drawable,
		sf::RenderWindow& Window)
{
	Window.draw(drawable);

}
} //namespace bhe
