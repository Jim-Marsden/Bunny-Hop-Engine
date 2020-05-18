//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "Entity.hpp"

Entity::Entity(const sf::Sprite &sprite) : Drawable(sprite) , speed{} {}

Entity::Entity(const sf::Texture &texture): speed{} {
    _sprite.setTexture(texture);

}


Entity::CollisionDirection Entity::isColliding(const std::vector<sf::RectangleShape> & Rectangles) const {
    CollisionDirection collisionDirection;
    for(auto & element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            return {isCollidingTop(element), isCollidingDown(element),
                    isCollidingLeft(element), isCollidingRight(element)};
        }
    }
    return {false, false, false , false};
}

bool Entity::isCollidingDown(sf::RectangleShape const  &Rectangles) const {

        if (_sprite.getGlobalBounds().intersects(Rectangles.getGlobalBounds())) {

            if((_sprite.getPosition().y - _sprite.getLocalBounds().height) < 0) {
                return true;
            }
        }
    return false;
}

bool Entity::isCollidingRight(sf::RectangleShape const &Rectangles) const {
    if (_sprite.getGlobalBounds().intersects(Rectangles.getGlobalBounds())) {

        if((_sprite.getPosition().x - _sprite.getLocalBounds().width) < 0) {
            return true;
        }
    }
    return false;
}

bool Entity::isCollidingLeft(sf::RectangleShape const &Rectangles) const {
    return !isCollidingRight(Rectangles);

}

bool Entity::isCollidingTop(const sf::RectangleShape &Rectangles) const {
   return !isCollidingDown(Rectangles);
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

sf::Vector2f Entity::GetSpeed() const {
    return speed;
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
