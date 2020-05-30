//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_PARALLAX_HPP
#define MOONLIGHT_TRAILS_PARALLAX_HPP

#include <SFML/Graphics.hpp>

 namespace mt {

    class parallax {
    protected:
        sf::Sprite sprite;
        float offset{0.0f};
    public:
        parallax() = default;
        explicit parallax(sf::Texture const & Texture, float Offset_in = 1);

        sf::Sprite const & GetSprite() const;

        void ApplyParallax(sf::Vector2f const & Player_speed);

        explicit operator sf::Sprite const &() const;
        explicit operator sf::Drawable const *() const;

        //explicit operator sf::Sprite & () ;

    };
}// namespace mt


#endif //MOONLIGHT_TRAILS_PARALLAX_HPP
