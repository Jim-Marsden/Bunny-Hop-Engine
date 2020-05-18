//
// Created by james on 5/15/2020.
//

#include "Parallax.hpp"

MT::Parallax::Parallax(const sf::Texture &texture, int offset_in) {
    _sprite.setTexture(texture);
    offset = offset_in;

}

sf::Sprite const &MT::Parallax::GetSprite() const {
    return _sprite;
}

void MT::Parallax::ApplyParallax(const sf::Vector2f &player_speed) {

    _sprite.move({(player_speed.x / offset),
                  player_speed.y / offset});
    //TODO stuff

}

MT::Parallax::operator sf::Sprite const &() const {
    return _sprite;
}

MT::Parallax::operator sf::Drawable const *() const {
    return &_sprite;
}

