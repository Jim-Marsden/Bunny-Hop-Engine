//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PARALLAX_HPP
#define MOONLIGHT_TRAILS_PARALLAX_HPP

#include <SFML/Graphics.hpp>

namespace MT {

    class Parallax {
        sf::Sprite _sprite;
        int offset;
    public:
        Parallax() = default;
        explicit Parallax(sf::Texture const & texture, int offset_in = 1);

        sf::Sprite const & GetSprite() const;

        void ApplyParallax(sf::Vector2f const & offset);

        explicit operator sf::Sprite const &() const;
        explicit operator sf::Drawable const *() const;

        //explicit operator sf::Sprite & () ;

    };
}// namespace MT


#endif //MOONLIGHT_TRAILS_PARALLAX_HPP
