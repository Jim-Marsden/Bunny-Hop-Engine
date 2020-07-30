//
// Created by james on 5/15/2020.
//

#include "drawable.hpp"

[[maybe_unused]] auto bhe::drawable::SetTexture(sf::Texture const &Texture) -> bhe::returnStatus<void> {
    sprite_.setTexture(Texture);
    return {};
}

auto bhe::drawable::SetPosition(float Top, float Left) -> bhe::returnStatus<void>{
    sprite_.setPosition(Top, Left);
    return {};
}

bhe::drawable::operator sf::Sprite const &() const { return sprite_; }

bhe::drawable::drawable(const sf::Sprite &Sprite) { sprite_ = Sprite; }

auto bhe::drawable::DoAnimation(std::chrono::microseconds const &Time) -> bhe::returnStatus<void>{
    if (!animation_information_.empty()) {

        if (animation_information_.size() > current_animation_) {
            auto &frame_data = animation_information_[current_animation_];

          frame_data.CountNextFrame(Time);
            sprite_.setTextureRect({static_cast<int>(frame_data.GetCurrentFameIndex().value) *
                                    sprite_.getTextureRect().width,
                                    0, sprite_.getTextureRect().height,
                                    sprite_.getTextureRect().width});

            return {};
        }
        return{false, bhe::ReturnStatusCode::OutOfRange};

    }
    return{false, bhe::ReturnStatusCode::Error};

}

auto bhe::drawable::SetTextureRect(const sf::IntRect &Rect) -> bhe::returnStatus<void> {
    sprite_.setTextureRect(Rect);
    return {};

}

auto bhe::drawable::AddAnimationState(const animationState &Animation_State) -> bhe::returnStatus<void>{
    animation_information_.emplace_back(Animation_State);
    return {};

}

auto bhe::drawable::SetOrigin(float Top, float Left) -> bhe::returnStatus<void>{
    sprite_.setOrigin(Top, Left);
    return {};

}
