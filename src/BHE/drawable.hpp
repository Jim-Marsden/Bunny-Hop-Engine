//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_ENGINE_DRAWABLE_HPP
#define BUNNY_HOP_ENGINE_DRAWABLE_HPP

#include "BHE/animationState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace bhe {
    class drawable {

    protected:
        sf::Sprite _sprite;
        int _current_frame_time{};

        std::vector<animationState> _animation_information{};
        std::size_t _current_animation{0};

    public:
        drawable() = default;

        explicit drawable(sf::Sprite const &Sprite);

        void SetTexture(sf::Texture const &Texture);

        void SetPosition(float Top, float Left);

        void SetOrigin(float Top, float Left);

        void SetTextureRect(sf::IntRect const &Rect);

        explicit operator sf::Sprite const &() const;

        void DoAnimation();

        void AddAnimationState(animationState const &Animation_state);
    };

} // namespace bhe

#endif // BUNNY_HOP_ENGINE_DRAWABLE_HPP