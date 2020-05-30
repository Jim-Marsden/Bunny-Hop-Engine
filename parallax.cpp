//
// Created by james on 5/15/2020.
//

#include "parallax.hpp"

mt::parallax::parallax(const sf::Texture &Texture, float Offset_in) {
    sprite.setTexture(Texture);
    offset = Offset_in;

}

sf::Sprite const &mt::parallax::GetSprite() const {
    return sprite;
}

void mt::parallax::ApplyParallax(const sf::Vector2f &Player_speed) {

    sprite.move({(Player_speed.x / offset),
                  Player_speed.y / offset});
    //TODO stuff

}

mt::parallax::operator sf::Sprite const &() const {
    return sprite;
}

mt::parallax::operator sf::Drawable const *() const {
    return &sprite;
}

