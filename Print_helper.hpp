//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PRINT_HELPER_HPP
#define MOONLIGHT_TRAILS_PRINT_HELPER_HPP

#include <SFML/Graphics.hpp>

inline namespace MT {
    template<class Sprite_Type>
    void do_draw(Sprite_Type const &spriteType, sf::RenderWindow &window) {
        window.draw(static_cast<sf::Sprite>(spriteType));
    }

    template<>
    void do_draw<sf::RectangleShape>(sf::RectangleShape const &shape,
                                     sf::RenderWindow &window) {
        window.draw(shape);

    }
} //namespace MT

#endif //MOONLIGHT_TRAILS_PRINT_HELPER_HPP
