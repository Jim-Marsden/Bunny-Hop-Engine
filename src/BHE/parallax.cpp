//
// Created by james on 5/15/2020.
//

#include "parallax.hpp"

bhe::parallax::parallax(const sf::Texture &Texture, float Offset_in) {
    _sprite.setTexture(Texture);
    _offset = Offset_in;

}

sf::Sprite const &bhe::parallax::GetSprite() const {
    return _sprite;
}

void bhe::parallax::ApplyParallax(const sf::Vector2f &Player_speed) {


    _sprite.setPosition(Player_speed.x / _offset,
                        Player_speed.y / _offset);
    //TODO stuff

}

bhe::parallax::operator sf::Sprite const &() const {
    return _sprite;
}

bhe::parallax::operator sf::Drawable const *() const {
    return &_sprite;
}

