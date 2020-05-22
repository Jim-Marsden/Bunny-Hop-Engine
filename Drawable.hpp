//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_DRAWABLE_HPP
#define MOONLIGHT_TRAILS_DRAWABLE_HPP
#include <SFML/Graphics.hpp>
inline namespace MT {
    class Drawable {

    protected:
        sf::Sprite _sprite;
    public:
        Drawable() = default;
        explicit Drawable(sf::Sprite const & sprite);

        void setTexture(sf::Texture const & texture);
        void setPosition(float top, float left);

        explicit operator sf::Sprite const &() const;

        //TODO Animations!

    };

    template<class ToDraw>
    int  set_animation_frame(ToDraw  & toDraw, int frame_to_wait, int current_frame, int number_of_frames);

    template<class ToDraw>
    int set_animation_frame( ToDraw &toDraw, int frame_to_wait, int current_frame, int number_of_frames) {
        auto sprite = static_cast<sf::Sprite>(toDraw);

        if((frame_to_wait % current_frame) == 1){
            ++current_frame;
            if(number_of_frames < current_frame){
                current_frame = 0;
            }
            sprite.setTextureRect({sprite.getTextureRect().left * current_frame,
                                   sprite.getTextureRect().top ,sprite.getTextureRect().width ,
                                   sprite.getTextureRect().height});

        }

        return current_frame;

    }

    template<class ToDraw>
    sf::Sprite set_animation_state(const ToDraw &toDraw, int offset) {
        return sf::Sprite();
    }

    template<class ToDraw> sf::Sprite set_animation_state(ToDraw const & toDraw, int offset);






}

#endif //MOONLIGHT_TRAILS_DRAWABLE_HPP
