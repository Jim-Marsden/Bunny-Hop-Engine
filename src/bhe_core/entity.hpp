//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_ENTITY_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_ENTITY_HPP

#include <bhe_core/drawable.hpp>
#include <bhe_core/movement.hpp>
#include <bhe_core/State_Machine.hpp>
#include <bhe_core/Return_Status.hpp>

#include <functional>

#include <chrono>

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
        collisionDirection collision_direction_{};
        long health_{};
        sf::Vector2f speed_;
        bool is_gravity_applied_{};

        movement movement_{};

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

        [[deprecated]] returnStatus<void> Move(std::chrono::duration<double> const & Speed);

        returnStatus<void> Move(std::chrono::microseconds const &Time);

        returnStatus<void> AddSpeed(sf::Vector2f const &Speed_In);

        returnStatus<void> AddSpeedY(float Y);

        returnStatus<void> AddSpeedX(float X);

        returnStatus<sf::Vector2f> GetSpeed() const;

        [[nodiscard]] returnStatus<decltype(health_)> GetHealth() const;

        returnStatus<void> SetHealth(int Health_In);

        returnStatus<void> AddMovement(std::string const &String_View, movement::movementDataT const &Movement_Data);


        // void DoAi();
        // void SetAIState(entity::AiStates const & state);
        //[[nodiscard]] entity::AiStates GetState() const;
    };

    returnStatus<void> DealDamage(entity &Entity, long Damage_Amount);

    returnStatus<void> DealDamage(entity &Entity, long Damage_Amount,
                                  std::function<void(entity &)> const &At_Zero);

} // namespace bhe

#endif // BUNNY_HOP_CORE_SRC_BHE_CORE_ENTITY_HPP
