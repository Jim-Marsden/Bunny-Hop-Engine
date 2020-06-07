//
// Created by james on 5/15/2020.
//

#include <iostream>
#include "entity.hpp"

bhe::entity::entity(const sf::Sprite &Sprite)
        : drawable(Sprite), _speed{} {}

bhe::entity::entity(const sf::Texture &Texture)
        : _speed{} {
    _sprite.setTexture(Texture);
}

//TODO: Helper functions

bhe::entity::collisionDirection
bhe::entity::IsColliding(const std::vector<sf::RectangleShape> &Rectangles) {
    _collision_direction.left = _collision_direction.right = _collision_direction.top = _collision_direction.bottom = false;
    for (auto const &element : Rectangles) {
        if (_sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if (IsCollidingTop(element)) {
                _sprite.setPosition(_sprite.getPosition().x, element.getGlobalBounds().top - _sprite.getOrigin().y);
                _collision_direction.top = true;
            }
            if (IsCollidingDown(element)) {
                _collision_direction.bottom = true;
            }
            if (IsCollidingLeft(element)) {
                _collision_direction.left = true;
            }
            if (IsCollidingRight(element)) {
                _collision_direction.right = true;
            }
        }
    }
    return _collision_direction;
}

bool bhe::entity::IsCollidingDown(sf::RectangleShape const &Rectangles) const {
    return _sprite.getGlobalBounds().top < Rectangles.getGlobalBounds().top;
}

bool bhe::entity::IsCollidingRight(sf::RectangleShape const &Rectangles) const {
    return _sprite.getGlobalBounds().left < Rectangles.getGlobalBounds().left;
}

bool bhe::entity::IsCollidingLeft(sf::RectangleShape const &Rectangles) const {
    return _sprite.getGlobalBounds().left <
           Rectangles.getGlobalBounds().left + Rectangles.getGlobalBounds().width;
}

bool bhe::entity::IsCollidingTop(const sf::RectangleShape &Rectangles) const {
    return _sprite.getGlobalBounds().top <
           Rectangles.getGlobalBounds().top + Rectangles.getGlobalBounds().height;
}

void bhe::entity::DoGravity(bool Doit) {
    if (Doit) {
        if (!_is_gravity_applied) {
            _speed.y += 2;
            _is_gravity_applied = true;
        }
    } else {
        if (_is_gravity_applied) {
            _speed.y -= 2;
            _is_gravity_applied = false;
        }
    }
}

decltype(bhe::entity::_health) bhe::entity::GetHealth() const { return _health; }

void bhe::entity::SetHealth(int Health_in) { _health = Health_in; }

void bhe::entity::Move() {

    _sprite.move(_movement.CalculateX(), _movement.CalculateY());
}

void bhe::entity::AddSpeed(const sf::Vector2f &Speed_in) { _speed += Speed_in; }

void bhe::entity::AddSpeedY(float Y) { _speed.y += Y; }

void bhe::entity::AddSpeedX(float X) { _speed.x += X; }

sf::Vector2f bhe::entity::GetSpeed() const { return _speed; }

void bhe::entity::AddMovement(std::string const &String_view, bhe::movement::movementDataT const &Movement_data) {
    _movement.AddData(String_view, Movement_data);
}


void bhe::deal_damage(entity &Entity, long Damage_amount) {
    auto amount{Entity.GetHealth() - Damage_amount};
    Entity.SetHealth(amount);
    if (Entity.GetHealth() < 1)
        Entity.SetHealth(0);
}

void bhe::deal_damage(entity &Entity, long Damage_amount,
                      std::function<void(entity &)> const &At_zero) {
    bhe::deal_damage(Entity, Damage_amount);
    if (Entity.GetHealth() < 1 && At_zero)
        At_zero(Entity);
}
