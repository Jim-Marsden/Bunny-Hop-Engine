//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_DRAWABLE_HPP
#define MOONLIGHT_TRAILS_DRAWABLE_HPP
#include <SFML/Graphics.hpp>
inline namespace MT {
    class Drawable {
    protected:
        sf::Sprite _sprite;
    public:
        Drawable() = default;
        explicit Drawable(sf::Sprite const & sprite);

        void setTexture(sf::Texture const & texture);
        void setPosition(float top, float left);

        explicit operator sf::Sprite const &() const;

        //TODO Animations!

    };
}

#endif //MOONLIGHT_TRAILS_DRAWABLE_HPP
