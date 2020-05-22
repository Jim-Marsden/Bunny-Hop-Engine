//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_ENTITY_HPP
#define MOONLIGHT_TRAILS_ENTITY_HPP

#include "State_Machine.h"
#include "Drawable.hpp"
#include <functional>

inline namespace MT {
    class Entity : public MT::Drawable {
    public:
        struct CollisionDirection{bool top, bottom, left, right;
        CollisionDirection()= default;} collision_direction;

        enum class AI_States{Default, Idle, Walking, Attacking, Falling, Jumping};

    protected:

        StateMachine<Entity::AI_States, void(*)Entity&> stateMachine;
        long health;
        sf::Vector2f speed;
        bool is_gravity_applied;

    public:
        Entity() = default;

        explicit Entity(sf::Sprite const &sprite);

        explicit Entity(sf::Texture const &texture);

        //TODO replace these with a single function for single faster checks
        CollisionDirection isColliding(std::vector<sf::RectangleShape> const &Rectangles) const;

        bool isCollidingDown(sf::RectangleShape const &Rectangles) const;

        bool isCollidingRight(sf::RectangleShape const &Rectangles) const;

        bool isCollidingLeft(sf::RectangleShape const &Rectangles) const;

        bool isCollidingTop(sf::RectangleShape const &Rectangles) const;

        void DoGravity(bool doit);

        void Move();

        void AddSpeed(sf::Vector2f const & speed_in);
        void AddSpeedY(float Y);
        void AddSpeedX(float X);

        sf::Vector2f GetSpeed() const;


        [[nodiscard]] decltype(health) GetHealth() const;

        void SetHealth(int health_in);

    };

    void deal_damage(Entity &entity, long damage_amount);
    void deal_damage(Entity &entity, long damage_amount, std::function<void(Entity &)> const & at_zero);
}


#endif //MOONLIGHT_TRAILS_ENTITY_HPP
