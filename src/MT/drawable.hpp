//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_DRAWABLE_HPP
#define MOONLIGHT_TRAILS_DRAWABLE_HPP
#include "animationState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace mt {
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

     void SetOrigin(float  Top, float   Left);

    void SetTextureRect(sf::IntRect const &Rect);

    explicit operator sf::Sprite const &() const;

    void DoAnimation();

    void AddAnimationState(animationState const &Animation_state);
};

} // namespace mt

#endif // MOONLIGHT_TRAILS_DRAWABLE_HPP
