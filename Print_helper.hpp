//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PRINT_HELPER_HPP
#define MOONLIGHT_TRAILS_PRINT_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>

inline namespace MT {
    template<class Sprite_Type>
    void do_draw(Sprite_Type const &drawable, sf::RenderWindow &window) {
        window.draw(static_cast<sf::Sprite>(drawable));
    }

    template<>
    void do_draw<sf::RectangleShape>(sf::RectangleShape const &drawable,
                                     sf::RenderWindow &window) {
        window.draw(drawable);

    }
} //namespace MT

#endif //MOONLIGHT_TRAILS_PRINT_HELPER_HPP
