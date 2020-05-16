//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_ENTITY_H
#define MOONLIGHT_TRAILS_ENTITY_H

#include "Drawable.h"

inline namespace MT {
class Entity : public MT::Drawable {
public:
    Entity() = default;
    explicit Entity(sf::Sprite const & sprite);
    explicit Entity(sf::Texture const & texture);

    //TODO replace these with a single function for single faster checks
    bool isColliding(std::vector<sf::RectangleShape> const &Rectangles) const;
    bool isCollidingDown(std::vector<sf::RectangleShape> const &Rectangles) const;
    bool isCollidingRight(std::vector<sf::RectangleShape> const &Rectangles) const;
    bool isCollidingLeft(std::vector<sf::RectangleShape> const &Rectangles) const;
    bool isCollidingTop(std::vector<sf::RectangleShape> const &Rectangles) const;

    void DoGravity(bool doit);


    };
} // namespace MT


#endif //MOONLIGHT_TRAILS_ENTITY_H
