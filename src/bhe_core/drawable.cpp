//
// Created by james on 5/15/2020.
//

#include "drawable.hpp"
#include <iostream>

void bhe::drawable::SetTexture(sf::Texture const &Texture) {
    _sprite.setTexture(Texture);
}

void bhe::drawable::SetPosition(float Top, float Left) {
    _sprite.setPosition(Top, Left);
}

bhe::drawable::operator sf::Sprite const &() const { return _sprite; }

bhe::drawable::drawable(const sf::Sprite &Sprite) { _sprite = Sprite; }

void bhe::drawable::DoAnimation() {
    if (!_animation_information.empty()) {
        if (_animation_information.size() > _current_animation) {
            auto &frame_data = _animation_information[_current_animation];
            if (frame_data.frames_per_animation_frame >=
                frame_data.current_frame_count) {
                ++frame_data.current_frame_count;
            } else {
                ++frame_data.sprite_index;
                frame_data.current_frame_count = 0;
                if (frame_data.sprite_index >= frame_data.number_of_frames)
                    frame_data.sprite_index = 0;
            }
            _sprite.setTextureRect({(static_cast<int>(frame_data.sprite_index)) *
                                    _sprite.getTextureRect().width,
                                    0, _sprite.getTextureRect().height,
                                    _sprite.getTextureRect().width});
        }

    } else {
        std::cout << "is empty\n";
    }
}

void bhe::drawable::DoAnimation(const std::chrono::duration<float> &time)
{
    if (!_animation_information.empty()) {


        if (_animation_information.size() > _current_animation) {
            auto &frame_data = _animation_information[_current_animation];
            if (frame_data.frames_per_animation_frame >=
                frame_data.current_frame_count) {
                ++frame_data.current_frame_count;
            } else {
                ++frame_data.sprite_index;
                frame_data.current_frame_count = 0;
                if (frame_data.sprite_index >= frame_data.number_of_frames)
                    frame_data.sprite_index = 0;
            }
            _sprite.setTextureRect({(static_cast<int>(frame_data.sprite_index)) *
                                    _sprite.getTextureRect().width,
                                    0, _sprite.getTextureRect().height,
                                    _sprite.getTextureRect().width});
        }

    }
}

void bhe::drawable::SetTextureRect(const sf::IntRect &Rect) {
    _sprite.setTextureRect(Rect);
}

void bhe::drawable::AddAnimationState(const animationState &Animation_state) {
    _animation_information.emplace_back(Animation_state);
}

void bhe::drawable::SetOrigin(float Top, float Left) {
    _sprite.setOrigin(Top, Left);

}
