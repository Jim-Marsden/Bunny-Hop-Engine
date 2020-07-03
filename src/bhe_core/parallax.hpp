//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PARALLAX_HPP
#define MOONLIGHT_TRAILS_PARALLAX_HPP

#include <SFML/Graphics.hpp>

namespace bhe {

    class parallax {
    protected:
        sf::Sprite _sprite;
        float _offset{0.0f};
    public:
        parallax() = default;

        ~parallax() = default;

        parallax(parallax &&) = default;

        parallax(parallax const &) = default;

        parallax &operator=(parallax &&) = default;

        parallax &operator=(parallax const &) = default;

        explicit parallax(sf::Texture const &Texture, float Offset_in = 1);

        sf::Sprite const &GetSprite() const;

        void ApplyParallax(sf::Vector2f const &Player_speed);

        explicit operator sf::Sprite const &() const;

        explicit operator sf::Drawable const *() const;

    };
}// namespace bhe


#endif //MOONLIGHT_TRAILS_PARALLAX_HPP
