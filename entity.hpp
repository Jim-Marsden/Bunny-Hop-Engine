//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_ENTITY_HPP
#define MOONLIGHT_TRAILS_ENTITY_HPP

#include "drawable.hpp"
#include "movement.hpp"
#include "State_Machine.h"
#include <functional>

namespace mt {
    class entity : public mt::drawable {
    public:


        struct collisionDirection {
            bool top, bottom, left, right;

            collisionDirection() = default;

            collisionDirection(collisionDirection &&Move) = default;

            collisionDirection(collisionDirection &Copy) = default;

            collisionDirection &operator=(collisionDirection const &) = default;
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
        [[nodiscard]] collisionDirection
        IsColliding(std::vector<sf::RectangleShape> const &Rectangles);

        [[nodiscard]] bool
        IsCollidingDown(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] bool
        IsCollidingRight(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] bool
        IsCollidingLeft(sf::RectangleShape const &Rectangles) const;

        [[nodiscard]] bool IsCollidingTop(sf::RectangleShape const &Rectangles) const;

        void DoGravity(bool Doit);

        void Move();

        void AddSpeed(sf::Vector2f const &Speed_in);

        void AddSpeedY(float Y);

        void AddSpeedX(float X);

        sf::Vector2f GetSpeed() const;

        [[nodiscard]] decltype(_health) GetHealth() const;

        void SetHealth(int Health_in);

        void AddMovement(std::string const &String_view, movement::movementDataT const &Movement_data);


        // void DoAi();
        // void SetAIState(entity::AiStates const & state);
        //[[nodiscard]] entity::AiStates GetState() const;
    };

    void deal_damage(entity &Entity, long Damage_amount);

    void deal_damage(entity &Entity, long Damage_amount,
                     std::function<void(entity & )> const &At_zero);

} // namespace mt

#endif // MOONLIGHT_TRAILS_ENTITY_HPP
