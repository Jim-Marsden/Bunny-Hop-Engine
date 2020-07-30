//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>

namespace bhe {
    template<class Sprite_Type>
    void DoDraw(Sprite_Type const &Drawable, sf::RenderWindow &Window) {
        Window.draw(static_cast<sf::Sprite>(Drawable));
    }

    template<>
    void DoDraw<sf::RectangleShape>(sf::RectangleShape const &Drawable,
                                    sf::RenderWindow &Window) {
        Window.draw(Drawable);

    }
} //namespace bhe

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PRINT_HELPER_HPP
