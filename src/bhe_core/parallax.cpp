//
// Created by james on 5/15/2020.
//

#include "parallax.hpp"

bhe::parallax::parallax(const sf::Texture &Texture, float Offset_In) {
    sprite_.setTexture(Texture);
  offset_ = Offset_In;

}

sf::Sprite const &bhe::parallax::GetSprite() const {
    return sprite_;
}

void bhe::parallax::ApplyParallax(const sf::Vector2f &Player_Speed) {


    sprite_.setPosition(Player_Speed.x / offset_,
                        Player_Speed.y / offset_);
    //TODO stuff

}

bhe::parallax::operator sf::Sprite const &() const {
    return sprite_;
}

bhe::parallax::operator sf::Drawable const *() const {
    return &sprite_;
}

