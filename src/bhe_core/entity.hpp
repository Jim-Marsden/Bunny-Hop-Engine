//
// Created by james on 5/15/2020.
//

#pragma once

#include "drawable.hpp"
#include "movement.hpp"
#include "State_Machine.hpp"
#include "Return_Status.hpp"

#include <functional>

#include <chrono>

namespace bhe {
    class Entity : public bhe::Drawable {
    public:


        struct collisionDirection {
            bool top, bottom, left, right;

            collisionDirection() = default;

            collisionDirection(collisionDirection &&move) = default;

            collisionDirection(collisionDirection &copy) = default;

            ~collisionDirection() = default;


            collisionDirection &operator=(collisionDirection const &) = default;

            collisionDirection &operator=(collisionDirection &&) = default;

        };


    protected:
        collisionDirection collision_direction{};
        long health{};
        sf::Vector2f speed;
        bool is_gravity_applied{};

        Movement movement{};

    public:

        explicit Entity(sf::Sprite const &sprite);

        explicit Entity(sf::Texture const &texture);

        // TODO replace these with a single function for single faster checks
        [[nodiscard]] returnStatus<collisionDirection>
        is_colliding(std::vector<sf::RectangleShape> const &rectangles);

        [[nodiscard]] static returnStatus<bool>
        is_colliding_down(sf::RectangleShape const &rectangles) ;

        [[nodiscard]] returnStatus<bool>
        is_colliding_right(sf::RectangleShape const &rectangles) const;

        [[nodiscard]] returnStatus<bool>
        is_colliding_left(sf::RectangleShape const &rectangles) const;

        [[nodiscard]] returnStatus<bool> is_colliding_top(sf::RectangleShape const &rectangles) const;

        returnStatus<void> do_gravity(bool doit);

        void move(std::chrono::microseconds const &speed);

        void add_speed(sf::Vector2f const &speed_in);

        void add_speed_y(float y);

        void add_speed_x(float x);

        sf::Vector2f get_speed() const;

        [[nodiscard]] long get_health() const;

        void set_health(int health_in);

        void add_movement(std::string const &string_view, Movement::movementDataT const &movement_data);


        // void DoAi();
        // void SetAIState(entity::AiStates const & state);
        //[[nodiscard]] entity::AiStates GetState() const;
    };

    bool deal_damage(Entity &entity, long damage_amount);

    void deal_damage(Entity &entity, long damage_amount,
                                  std::function<void(Entity &)> const &at_zero);

} // namespace bhe
