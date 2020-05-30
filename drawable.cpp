//
// Created by james on 5/15/2020.
//

#include "drawable.hpp"
#include <iostream>

void mt::drawable::SetTexture(sf::Texture const &Texture) {
    sprite.setTexture(Texture);
}

void mt::drawable::SetPosition(float Top, float Left) {
    sprite.setPosition(Top, Left);
}

mt::drawable::operator sf::Sprite const &() const { return sprite; }

mt::drawable::drawable(const sf::Sprite &Sprite) { sprite = Sprite; }

void mt::drawable::DoAnimation() {
    if (!animation_information.empty()) {
        if (animation_information.size() > current_animation) {
            auto &frame_data = animation_information[current_animation];
            if (frame_data.frames_per_animation_frame >=
                frame_data.current_frame_count) {
                ++frame_data.current_frame_count;
            } else {
                ++frame_data.sprite_index;
                frame_data.current_frame_count = 0;
                if (frame_data.sprite_index >= frame_data.number_of_frames)
                    frame_data.sprite_index = 0;
            }
            sprite.setTextureRect({(static_cast<int>(frame_data.sprite_index)) *
                                   sprite.getTextureRect().width,
                                   0, sprite.getTextureRect().height,
                                   sprite.getTextureRect().width});
        }

    } else {
        std::cout << "is empty\n";
    }
}

void mt::drawable::SetTextureRect(const sf::IntRect &Rect) {
    sprite.setTextureRect(Rect);
}

void mt::drawable::AddAnimationState(const animationState &Animation_state) {
    animation_information.emplace_back(Animation_state);
}
