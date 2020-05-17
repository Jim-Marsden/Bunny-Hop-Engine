//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "Entity.hpp"

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


            auto x{_sprite.getLocalBounds().top - _sprite.getLocalBounds().top};
            auto xs{_sprite.getPosition().y - _sprite.getLocalBounds().height};
            auto y{element.getLocalBounds().top - element.getLocalBounds().height};
            //std::cout << "xs" << xs << "X" << x << "y" << y <<  " x&y" << (( x < 0 ? -x : x /2) > y) << "Entity::isCollidingDown\n";

            if((_sprite.getPosition().y - _sprite.getLocalBounds().height) < 0) {
                std::cout << "bounce!~\n";
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
    if(doit) {
        if(!is_gravity_applied) {
            speed.y += 2;
            is_gravity_applied = true;
        }
    }
    else{
        if(is_gravity_applied){
            speed.y -= 2;
            is_gravity_applied = false;
        }
    }


}

decltype(Entity::health) Entity::GetHealth() const {
    return health;
}

void Entity::SetHealth(int health_in) {
    health = health_in;

}

void Entity::Move() {
    _sprite.move(speed);

}

void Entity::AddSpeed(const sf::Vector2f &speed_in) {
    speed += speed_in;

}

void Entity::AddSpeedY(float Y) {
    speed.y += Y;

}

void Entity::AddSpeedX(float X) {
    speed.x += X;

}



void MT::deal_damage(Entity &entity, long damage_amount) {
    auto amount{ entity.GetHealth() - damage_amount};
    entity.SetHealth(amount);
    if(entity.GetHealth() < 1) entity.SetHealth(0);

}

void MT::deal_damage(Entity &entity, long damage_amount, std::function<void(Entity &)> const & at_zero) {
    MT::deal_damage(entity, damage_amount);
    if(entity.GetHealth() < 1 && at_zero)at_zero(entity);
}
