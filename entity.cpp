//
// Created by james on 5/15/2020.
//

#include "entity.hpp"

mt::entity::entity(const sf::Sprite &Sprite)
        : drawable(Sprite), speed{}, current_state{AiStates::Default} {}

mt::entity::entity(const sf::Texture &Texture)
        : speed{}, current_state{AiStates::Default} {
    sprite.setTexture(Texture);
}

mt::entity::collisionDirection
mt::entity::IsColliding(const std::vector<sf::RectangleShape> &Rectangles) {
    collision_direction = {false, false, false, false};
    for (auto const &element : Rectangles) {
        if (sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if (IsCollidingTop(element))
                collision_direction.top = true;
            if (IsCollidingDown(element))
                collision_direction.bottom = true;
            if (IsCollidingLeft(element))
                collision_direction.left = true;
            if (IsCollidingRight(element))
                collision_direction.right = true;
        }
    }
    return collision_direction;
}

bool mt::entity::IsCollidingDown(sf::RectangleShape const &Rectangles) const {
    return sprite.getGlobalBounds().top < Rectangles.getGlobalBounds().top;
}

bool mt::entity::IsCollidingRight(sf::RectangleShape const &Rectangles) const {
    return sprite.getGlobalBounds().left < Rectangles.getGlobalBounds().left;
}

bool mt::entity::IsCollidingLeft(sf::RectangleShape const &Rectangles) const {
    return sprite.getGlobalBounds().left <
           Rectangles.getGlobalBounds().left + Rectangles.getGlobalBounds().width;
}

bool mt::entity::IsCollidingTop(const sf::RectangleShape &Rectangles) const {
    return sprite.getGlobalBounds().top <
           Rectangles.getGlobalBounds().top + Rectangles.getGlobalBounds().height;
}

void mt::entity::DoGravity(bool Doit) {
    if (Doit) {
        if (!is_gravity_applied) {
            speed.y += 2;
            is_gravity_applied = true;
        }
    } else {
        if (is_gravity_applied) {
            speed.y -= 2;
            is_gravity_applied = false;
        }
    }
}

decltype(mt::entity::health) mt::entity::GetHealth() const { return health; }

void mt::entity::SetHealth(int Health_in) { health = Health_in; }

void mt::entity::Move() { sprite.move(speed); }

void mt::entity::AddSpeed(const sf::Vector2f &Speed_in) { speed += Speed_in; }

void mt::entity::AddSpeedY(float Y) { speed.y += Y; }

void mt::entity::AddSpeedX(float X) { speed.x += X; }

sf::Vector2f mt::entity::GetSpeed() const { return speed; }

void mt::deal_damage(entity &Entity, long Damage_amount) {
    auto amount{Entity.GetHealth() - Damage_amount};
    Entity.SetHealth(amount);
    if (Entity.GetHealth() < 1)
        Entity.SetHealth(0);
}

void mt::deal_damage(entity &Entity, long Damage_amount,
                     std::function<void(entity & )> const &At_zero) {
    mt::deal_damage(Entity, Damage_amount);
    if (Entity.GetHealth() < 1 && At_zero)
        At_zero(Entity);
}
