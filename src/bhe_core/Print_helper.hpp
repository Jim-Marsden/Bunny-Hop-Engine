//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP

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

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP
