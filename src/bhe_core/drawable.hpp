//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_ENGINE_DRAWABLE_HPP
#define BUNNY_HOP_ENGINE_DRAWABLE_HPP

#include <bhe_core/animationState.hpp>
#include <bhe_core/Return_Status.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>


namespace bhe {
    class drawable {

    protected:
        sf::Sprite _sprite;
        float _current_frame_time{0.0F};

        std::vector<animationState> _animation_information{};
        std::size_t _current_animation{0};

    public:
        drawable() = default;

        drawable(drawable const &) = default;

        drawable(drawable &&) = default;

        ~drawable() = default;

        drawable &operator=(drawable &&) = default;

        drawable &operator=(drawable const &) = default;
        explicit operator sf::Sprite const &() const;



        explicit drawable(sf::Sprite const &Sprite);

        auto SetTexture(sf::Texture const &Texture) ->  bhe::returnStatus<void>;

        auto SetPosition(float Top, float Left)  -> returnStatus<void>;

        auto SetOrigin(float Top, float Left) -> returnStatus<void>;

        auto SetTextureRect(sf::IntRect const &Rect) -> returnStatus<void>;


        auto DoAnimation(std::chrono::microseconds const &time) -> returnStatus<void>;

        auto AddAnimationState(animationState const &Animation_state) -> returnStatus<void>;
    };

} // namespace bhe

#endif // BUNNY_HOP_ENGINE_DRAWABLE_HPP
