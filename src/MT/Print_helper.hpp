//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PRINT_HELPER_HPP
#define MOONLIGHT_TRAILS_PRINT_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>

namespace mt {
    template<class Sprite_Type>
    void do_draw(Sprite_Type const &Drawable, sf::RenderWindow &Window) {
        Window.draw(static_cast<sf::Sprite>(Drawable));
    }

    template<>
    void do_draw<sf::RectangleShape>(sf::RectangleShape const &Drawable,
                                     sf::RenderWindow &Window) {
        Window.draw(Drawable);

    }
} //namespace mt

#endif //MOONLIGHT_TRAILS_PRINT_HELPER_HPP
