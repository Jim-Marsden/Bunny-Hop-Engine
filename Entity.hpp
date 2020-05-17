//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_ENTITY_HPP
#define MOONLIGHT_TRAILS_ENTITY_HPP

#include "Drawable.hpp"
#include <functional>

inline namespace MT {
    class Entity : public MT::Drawable {

    protected:

        long health;
        sf::Vector2f speed;
        bool is_gravity_applied;

    public:
        Entity() = default;

        explicit Entity(sf::Sprite const &sprite);

        explicit Entity(sf::Texture const &texture);

        //TODO replace these with a single function for single faster checks
        bool isColliding(std::vector<sf::RectangleShape> const &Rectangles) const;

        bool isCollidingDown(std::vector<sf::RectangleShape> const &Rectangles) const;

        bool isCollidingRight(std::vector<sf::RectangleShape> const &Rectangles) const;

        bool isCollidingLeft(std::vector<sf::RectangleShape> const &Rectangles) const;

        bool isCollidingTop(std::vector<sf::RectangleShape> const &Rectangles) const;

        void DoGravity(bool doit);

        void Move();

        void AddSpeed(sf::Vector2f const & speed_in);
        void AddSpeedY(float Y);
        void AddSpeedX(float X);


        [[nodiscard]] decltype(health) GetHealth() const;

        void SetHealth(int health_in);

    };

    void deal_damage(Entity &entity, long damage_amount);
    void deal_damage(Entity &entity, long damage_amount, std::function<void(Entity &)> const & at_zero);
}


#endif //MOONLIGHT_TRAILS_ENTITY_HPP
