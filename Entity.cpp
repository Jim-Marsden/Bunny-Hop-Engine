//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "Entity.hpp"

MT::Entity::Entity(const sf::Sprite &sprite) : Drawable(sprite) , speed{}, _current_state{AI_States::Default} {}

MT::Entity::Entity(const sf::Texture &texture): speed{}, _current_state{AI_States::Default} {
    _sprite.setTexture(texture);

}


MT::Entity::CollisionDirection MT::Entity::isColliding(const std::vector<sf::RectangleShape> & Rectangles) const {
    for(auto & element : Rectangles) {
        if(_sprite.getGlobalBounds().intersects(element.getGlobalBounds())){
            return {isCollidingTop(element), isCollidingDown(element),
                    isCollidingLeft(element), isCollidingRight(element)};
        }
    }

    return {false, false, false , false};
}

bool MT::Entity::isCollidingDown(sf::RectangleShape const  &Rectangles) const {
    return _sprite.getGlobalBounds().top  < Rectangles.getGlobalBounds().top;
}

bool MT::Entity::isCollidingRight(sf::RectangleShape const &Rectangles) const {
    return _sprite.getGlobalBounds().left  < Rectangles.getGlobalBounds().left;
}

bool MT::Entity::isCollidingLeft(sf::RectangleShape const &Rectangles) const {
    return _sprite.getGlobalBounds().left  < Rectangles.getGlobalBounds().left + Rectangles.getGlobalBounds().width;
}

bool MT::Entity::isCollidingTop(const sf::RectangleShape &Rectangles) const {
    return _sprite.getGlobalBounds().top  < Rectangles.getGlobalBounds().top + Rectangles.getGlobalBounds().height;
}

void MT::Entity::DoGravity(bool doit) {
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

decltype(MT::Entity::health) MT::Entity::GetHealth() const {
    return health;
}

void MT::Entity::SetHealth(int health_in) {
    health = health_in;

}

void MT::Entity::Move() {
    _sprite.move(speed);

}

void MT::Entity::AddSpeed(const sf::Vector2f &speed_in) {
    speed += speed_in;

}

void MT::Entity::AddSpeedY(float Y) {
    speed.y += Y;

}

void MT::Entity::AddSpeedX(float X) {
    speed.x += X;

}

sf::Vector2f MT::Entity::GetSpeed() const {
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
