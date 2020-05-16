//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "Entity.h"

Entity::Entity(const sf::Sprite &sprite) : Drawable(sprite) {}

Entity::Entity(const sf::Texture &texture) {
    _sprite.setTexture(texture);

}


bool Entity::isColliding(const std::vector<sf::RectangleShape> & Rectangles) const {
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

bool Entity::isCollidingDown(const std::vector<sf::RectangleShape> &Rectangles) const {
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if(_sprite.getGlobalBounds().height < element.getGlobalBounds().height) {
                std::cout << "Entity::isCollidingDown\n";
                return true;
            }
        }
    }
    return false;
}

bool Entity::isCollidingRight(const std::vector<sf::RectangleShape> &Rectangles) const {
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if(_sprite.getGlobalBounds().left < element.getGlobalBounds().left) {
                std::cout << "Entity::isCollidingRight\n";
                return true;
            }
        }
    }
    return false;
}

bool Entity::isCollidingLeft(const std::vector<sf::RectangleShape> &Rectangles) const {
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if(_sprite.getGlobalBounds().left > element.getGlobalBounds().left) {
                std::cout << "Entity::isCollidingLeft\n";
                return true;
            }
        }
    }
    return false;
}

bool Entity::isCollidingTop(const std::vector<sf::RectangleShape> &Rectangles) const {
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if(_sprite.getGlobalBounds().height > element.getGlobalBounds().height) {
                std::cout << "Entity::isCollidingTop\n";
                return true;
            }
        }
    }
    return false;
}

void Entity::DoGravity(bool doit) {
    if(doit)
        _sprite.move({0.0f, 1.0f});

}


