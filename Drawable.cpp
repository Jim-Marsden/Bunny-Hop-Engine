//
// Created by james on 5/15/2020.
//

#include "Drawable.h"

void Drawable::setTexture(sf::Texture const &texture) {
    _sprite.setTexture(texture);

}

void Drawable::setPosition(float top, float left) {
    _sprite.setPosition(top, left);
}

Drawable::operator sf::Sprite const &() const {
    return _sprite;
}

Drawable::Drawable(const sf::Sprite &sprite) {
    _sprite = sprite;

}
