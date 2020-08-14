//
// Created by james on 5/15/2020.
//

#include <limits>
#include "entity.hpp"
#include <iostream>

bhe::entity::entity(const sf::Sprite &Sprite)
    : drawable(Sprite), speed_{} {}

bhe::entity::entity(const sf::Texture &Texture)
    : speed_{} {
    sprite_.setTexture(Texture);
}

//TODO: Helper functions

bhe::returnStatus<bhe::entity::collisionDirection>
bhe::entity::IsColliding(const std::vector<sf::RectangleShape> &Rectangles) {
  collision_direction_.left = collision_direction_.right = collision_direction_.top = collision_direction_.bottom = false;
    for (auto const &element : Rectangles) {
        if (sprite_.getGlobalBounds().intersects(element.getGlobalBounds())) {
            if (IsCollidingTop(element).value) {
                //sprite_.setPosition(sprite_.getPosition().x, element.getGlobalBounds().top - sprite_.getOrigin().y);
              auto move_amount_test = ((sprite_.getGlobalBounds().height + sprite_.getGlobalBounds().top)) -(( element.getGlobalBounds().height + element.getGlobalBounds().top));
              //sprite_.move(0, move_amount_test);//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));

              collision_direction_.top = true;
            }
            if (IsCollidingDown(element).value) {
              sprite_.move(0, element.getGlobalBounds().top - (sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().height));//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));
              collision_direction_.bottom = true;
            }
            if (IsCollidingLeft(element).value) {
              collision_direction_.left = true;
            }
            if (IsCollidingRight(element).value) {
              collision_direction_.right = true;
            }
        }
    }
    return {collision_direction_};
}

bhe::returnStatus<bool> bhe::entity::IsCollidingDown(sf::RectangleShape const &Rectangles) const {
  return{true};//{(sprite_.getGlobalBounds().height + sprite_.getGlobalBounds().top) / 2 <= (Rectangles.getGlobalBounds().height + Rectangles.getGlobalBounds().top) /2};

  //return {(sprite_.getGlobalBounds().top < Rectangles.getGlobalBounds().top)};
}

bhe::returnStatus<bool> bhe::entity::IsCollidingRight(sf::RectangleShape const &Rectangles) const {
    return {(sprite_.getGlobalBounds().left < Rectangles.getGlobalBounds().left)};
}

bhe::returnStatus<bool> bhe::entity::IsCollidingLeft(sf::RectangleShape const &Rectangles) const {
    return {(sprite_.getGlobalBounds().left <
             Rectangles.getGlobalBounds().left + Rectangles.getGlobalBounds().width)};
}

bhe::returnStatus<bool> bhe::entity::IsCollidingTop(const sf::RectangleShape &Rectangles) const {
  return{(sprite_.getGlobalBounds().height + sprite_.getGlobalBounds().top) / 2 >= (Rectangles.getGlobalBounds().height + Rectangles.getGlobalBounds().top) /2};

  //return {(sprite_.getGlobalBounds().top <
    //         Rectangles.getGlobalBounds().top + Rectangles.getGlobalBounds().height)};
}

bhe::returnStatus<void> bhe::entity::DoGravity(bool Doit) {
    if (Doit) {
        if (!is_gravity_applied_) {
          //speed_.y += 2;
          is_gravity_applied_ = true;
        }
    } else {
        if (is_gravity_applied_) {
          //speed_.y -= 2;
          is_gravity_applied_ = false;
        }
    }
    return {};
}

bhe::returnStatus<decltype(bhe::entity::health_)> bhe::entity::GetHealth() const { return {health_}; }

bhe::returnStatus<void> bhe::entity::SetHealth(int Health_In) {
  health_ = Health_In;
    return {};
}

bhe::returnStatus<void> bhe::entity::Move(const std::chrono::microseconds &Time) {
  auto calculate_directions = [](auto const &Speed, std::chrono::duration<double, std::milli> const &Time_Local) -> float {
    auto const result = (static_cast<int>( Speed) != 0) ? (  (Time_Local.count()) / Speed) : 0;
    std::cout << result << '\n';
    return result;
  };

  sprite_.move(calculate_directions(movement_.CalculateX(), Time), calculate_directions(movement_.CalculateY(), Time));
  return{};
}

bhe::returnStatus<void> bhe::entity::Move(std::chrono::duration<double> const &Time) {
    auto calculate_directions = [](auto const &Speed, std::chrono::duration<double> const &Time_Local) {
        return (Time_Local.count() + 1) * Speed;
    };

    sprite_.move(calculate_directions(movement_.CalculateX(), Time), calculate_directions(movement_.CalculateY(), Time));
    return{};
}

bhe::returnStatus<void> bhe::entity::AddSpeed(const sf::Vector2f &Speed_In) {
  speed_ += Speed_In;
    return {};
}

bhe::returnStatus<void> bhe::entity::AddSpeedY(float Y) {
  speed_.y += Y;
    return {};
}

bhe::returnStatus<void> bhe::entity::AddSpeedX(float X) {
  speed_.x += X;
    return {};
}

bhe::returnStatus<sf::Vector2f> bhe::entity::GetSpeed() const {
    return {speed_};
}

bhe::returnStatus<void> bhe::entity::AddMovement(std::string const &String_View, bhe::movement::movementDataT const &Movement_Data) {
    movement_.AddData(String_View, Movement_Data);
    return {};
}


bhe::returnStatus<void> bhe::DealDamage(entity &Entity, long Damage_Amount) {
    if(auto [health, normal, code] = Entity.GetHealth(); normal) {
        auto amount{health - Damage_Amount};
        Entity.SetHealth(amount);
        if (Entity.GetHealth().value < 1)
            Entity.SetHealth(0);

        return {};
    }
    else{
        return{normal, code};
    }
}

bhe::returnStatus<void> bhe::DealDamage(entity &Entity, long Damage_Amount,
                                        std::function<void(entity &)> const &At_Zero) {
  bhe::DealDamage(Entity, Damage_Amount);
    if (Entity.GetHealth().value < 1 && At_Zero)
        At_Zero(Entity);

    return {};
}
