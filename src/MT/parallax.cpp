//
// Created by james on 5/15/2020.
//

#include "parallax.hpp"

mt::parallax::parallax(const sf::Texture &Texture, float Offset_in) {
    _sprite.setTexture(Texture);
    _offset = Offset_in;

}

sf::Sprite const &mt::parallax::GetSprite() const {
    return _sprite;
}

void mt::parallax::ApplyParallax(const sf::Vector2f &Player_speed) {


    _sprite.setPosition(Player_speed.x / _offset,
                        Player_speed.y / _offset);
    //TODO stuff

}

mt::parallax::operator sf::Sprite const &() const {
    return _sprite;
}

mt::parallax::operator sf::Drawable const *() const {
    return &_sprite;
}

