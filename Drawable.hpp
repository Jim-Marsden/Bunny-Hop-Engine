//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_DRAWABLE_HPP
#define MOONLIGHT_TRAILS_DRAWABLE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimationState.hpp"

inline namespace MT {
    class Drawable {

    protected:
        sf::Sprite _sprite;
        int current_frame_time{};

        std::vector<AnimationState> _animation_information{};
        std::size_t _current_aniomation{0};

    public:
        Drawable() = default;

        explicit Drawable(sf::Sprite const &sprite);

        void setTexture(sf::Texture const &texture);

        void setPosition(float top, float left);

        void setTextureRect(sf::IntRect const & rect);

        explicit operator sf::Sprite const &() const;

        void DoAnimation(uint_fast64_t frame_count);

        void AddAnimationState(AnimationState const & animationState);




    };



}

#endif //MOONLIGHT_TRAILS_DRAWABLE_HPP
