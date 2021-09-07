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
    class Entity : public bhe::Drawable {
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

        Movement movement_{};

    public:

        explicit Entity(sf::Sprite const &sprite);

        explicit Entity(sf::Texture const &texture);

        // TODO replace these with a single function for single faster checks
        [[nodiscard]] returnStatus<collisionDirection>
        is_colliding(std::vector<sf::RectangleShape> const &rectangles);

        [[nodiscard]] static returnStatus<bool>
        is_colliding_down(sf::RectangleShape const &Rectangles) ;

        [[nodiscard]] returnStatus<bool>
        is_colliding_right(sf::RectangleShape const &rectangles) const;

        [[nodiscard]] returnStatus<bool>
        is_colliding_left(sf::RectangleShape const &rectangles) const;

        [[nodiscard]] returnStatus<bool> is_colliding_top(sf::RectangleShape const &rectangles) const;

        returnStatus<void> do_gravity(bool doit);

        [[deprecated]] returnStatus<void> move(std::chrono::duration<double> const & speed);

        returnStatus<void> move(std::chrono::microseconds const &Time);

        returnStatus<void> add_speed(sf::Vector2f const &speed_in);

        returnStatus<void> add_speed_y(float y);

        returnStatus<void> add_speed_x(float x);

        returnStatus<sf::Vector2f> get_speed() const;

        [[nodiscard]] returnStatus<decltype(health_)> get_health() const;

        returnStatus<void> set_health(int health_in);

        returnStatus<void> add_movement(std::string const &string_view, Movement::movementDataT const &movement_data);


        // void DoAi();
        // void SetAIState(entity::AiStates const & state);
        //[[nodiscard]] entity::AiStates GetState() const;
    };

    returnStatus<void> deal_damage(Entity &entity, long damage_amount);

    returnStatus<void> deal_damage(Entity &entity, long damage_amount,
                                  std::function<void(Entity &)> const &at_zero);

} // namespace bhe

#endif // BUNNY_HOP_CORE_SRC_BHE_CORE_ENTITY_HPP
