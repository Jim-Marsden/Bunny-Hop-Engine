//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP

#include <SFML/Graphics.hpp>

namespace bhe {

    class parallax {
    protected:
        sf::Sprite sprite_;
        float offset_{0.0f};
    public:
        parallax() = default;

        ~parallax() = default;

        parallax(parallax &&) = default;

        parallax(parallax const &) = default;

        parallax &operator=(parallax &&) = default;

        parallax &operator=(parallax const &) = default;

        explicit parallax(sf::Texture const &Texture, float Offset_In = 1);

        sf::Sprite const &GetSprite() const;

        void ApplyParallax(sf::Vector2f const &Player_Speed);

        explicit operator sf::Sprite const &() const;

        explicit operator sf::Drawable const *() const;

    };
}// namespace bhe


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP
