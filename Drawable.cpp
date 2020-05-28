//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "Drawable.hpp"

void MT::Drawable::setTexture(sf::Texture const &texture) {
    _sprite.setTexture(texture);

}

void MT::Drawable::setPosition(float top, float left) {
    _sprite.setPosition(top, left);
}

MT::Drawable::operator sf::Sprite const &() const {
    return _sprite;
}

MT::Drawable::Drawable(const sf::Sprite &sprite) {
    _sprite = sprite;

}

void MT::Drawable::DoAnimation(uint_fast64_t frame_count) {
    if(!_animation_information.empty()){
        if(_animation_information.size() > _current_aniomation){
            auto & frame_data = _animation_information[_current_aniomation];
            if(frame_data.frames_per_animation_frame >= frame_data.current_frame_count) {
               ++frame_data.current_frame_count;
            }
            else{
                ++frame_data.sprite_index;
                frame_data.current_frame_count = 0;
                if (frame_data.sprite_index >= frame_data.number_of_frames)
                    frame_data.sprite_index = 0;
            }
            _sprite.setTextureRect({(static_cast<int>(frame_data.sprite_index)) *_sprite.getTextureRect().width, 0, _sprite.getTextureRect().height, _sprite.getTextureRect().width});


        }

    }
    else{
        std::cout << "is empty\n";
    }

}

void MT::Drawable::setTextureRect(const sf::IntRect &rect) {
    _sprite.setTextureRect(rect);

}

void MT::Drawable::AddAnimationState(const AnimationState &animationState) {
    _animation_information.emplace_back(animationState);

}
