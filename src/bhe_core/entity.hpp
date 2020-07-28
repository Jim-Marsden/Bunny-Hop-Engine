//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_ENTITY_HPP
#define MOONLIGHT_TRAILS_ENTITY_HPP

#include "drawable.hpp"
#include "movement.hpp"
#include "State_Machine.h"
#include <functional>

#include <chrono>
#include <bhe_core/Return_Status.hpp>

namespace bhe {
    class entity : public bhe::drawable {
    public:


        struct collisionDirection {
            bool top, bottom, left, right;

            collisionDirection() = default;

            collisionDirection(collisionDirection &&Move) = default;

            collisionDirection(collisionDirection &Copy) = default;

            ~collisionDirection() = default;


            collisionDirection &operator=(collisionDirection const &) = default;

            collisionDirection &operator=(collisionDirection &&) = default;

        };


    protected:
        collisionDirection _collision_direction{};
        long _health{};
        sf::Vector2f _speed;
        bool _is_gravity_applied{};

        movement _movement{};

    public:

        explicit entity(sf::Sprite const &Sprite);

        explicit entity(sf::Texture const &Texture);

        // TODO replace these with a single function for single faster checks
        [[nodiscard]] returnStatus<collisionDirection>
        IsColliding(std::vector<sf::RectangleShape> const &Rectangles);

        [[nodiscard]] returnStatus<bool>
        IsCollidingDown(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] returnStatus<bool>
        IsCollidingRight(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] returnStatus<bool>
        IsCollidingLeft(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] returnStatus<bool> IsCollidingTop(sf::RectangleShape const &Rectangles) const;

        returnStatus<void> DoGravity(bool Doit);

        returnStatus<void> Move(std::chrono::duration<double> const & time);

        returnStatus<void> AddSpeed(sf::Vector2f const &Speed_in);

        returnStatus<void> AddSpeedY(float Y);

        returnStatus<void> AddSpeedX(float X);

        returnStatus<sf::Vector2f> GetSpeed() const;

        [[nodiscard]] returnStatus<decltype(_health)> GetHealth() const;

        returnStatus<void> SetHealth(int Health_in);

        returnStatus<void> AddMovement(std::string const &String_view, movement::movementDataT const &Movement_data);


        // void DoAi();
        // void SetAIState(entity::AiStates const & state);
        //[[nodiscard]] entity::AiStates GetState() const;
    };

    returnStatus<void> deal_damage(entity &Entity, long Damage_amount);

    returnStatus<void> deal_damage(entity &Entity, long Damage_amount,
                     std::function<void(entity &)> const &At_zero);

} // namespace bhe

#endif // MOONLIGHT_TRAILS_ENTITY_HPP
