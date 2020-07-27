//
// Created by james on 5/15/2020.
//

#include "drawable.hpp"
#include <iostream>

auto bhe::drawable::SetTexture(sf::Texture const &Texture) -> bhe::returnStatus<void> {
    _sprite.setTexture(Texture);
    return {};
}

auto bhe::drawable::SetPosition(float Top, float Left) -> bhe::returnStatus<void>{
    _sprite.setPosition(Top, Left);
    return {};
}

bhe::drawable::operator sf::Sprite const &() const { return _sprite; }

bhe::drawable::drawable(const sf::Sprite &Sprite) { _sprite = Sprite; }

auto bhe::drawable::DoAnimation(std::chrono::microseconds const &time) -> bhe::returnStatus<void>{
    if (!_animation_information.empty()) {

        if (_animation_information.size() > _current_animation) {
            auto &frame_data = _animation_information[_current_animation];

            frame_data.countNextFrame(time);
            _sprite.setTextureRect({static_cast<int>(frame_data.getCurrentFameIndex().value) *
                                    _sprite.getTextureRect().width,
                                    0, _sprite.getTextureRect().height,
                                    _sprite.getTextureRect().width});

            return {};
        }
        return{false, bhe::returnStatusCode::Error};

    }
    return{false, bhe::returnStatusCode::Error};

}

auto bhe::drawable::SetTextureRect(const sf::IntRect &Rect) -> bhe::returnStatus<void> {
    _sprite.setTextureRect(Rect);
    return {};

}

auto bhe::drawable::AddAnimationState(const animationState &Animation_state) -> bhe::returnStatus<void>{
    _animation_information.emplace_back(Animation_state);
    return {};

}

auto bhe::drawable::SetOrigin(float Top, float Left) -> bhe::returnStatus<void>{
    _sprite.setOrigin(Top, Left);
    return {};

}
