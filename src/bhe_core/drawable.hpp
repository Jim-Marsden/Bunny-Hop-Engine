//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_DRAWABLE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_DRAWABLE_HPP

#include <bhe_core/animationState.hpp>
#include <bhe_core/Return_Status.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>


namespace bhe {
    class drawable {

    protected:
        sf::Sprite sprite_;
        //float current_frame_time_{0.0F};

        std::vector<animationState> animation_information_{};
        std::size_t current_animation_{0};

    public:
        drawable() = default;

        drawable(drawable const &) = default;

        drawable(drawable &&) = default;

        ~drawable() = default;

        drawable &operator=(drawable &&) = default;

        drawable &operator=(drawable const &) = default;
        explicit operator sf::Sprite const &() const;



        explicit drawable(sf::Sprite const &Sprite);

      [[maybe_unused]] auto SetTexture(sf::Texture const &Texture) ->  bhe::returnStatus<void>;

        auto SetPosition(float Top, float Left)  -> returnStatus<void>;

        auto SetOrigin(float Top, float Left) -> returnStatus<void>;

        auto SetTextureRect(sf::IntRect const &Rect) -> returnStatus<void>;


        auto DoAnimation(std::chrono::microseconds const &Time) -> returnStatus<void>;

        auto AddAnimationState(animationState const &Animation_State) -> returnStatus<void>;
    };

} // namespace bhe

#endif // BUNNY_HOP_CORE_SRC_BHE_CORE_DRAWABLE_HPP
