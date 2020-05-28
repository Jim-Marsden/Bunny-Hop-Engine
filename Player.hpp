//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_PLAYER_HPP
#define MOONLIGHT_TRAILS_PLAYER_HPP

#include "Entity.hpp"
namespace MT {
    class Player : public MT::Entity {
    public:
        Player() = default;
        explicit Player(sf::Sprite const & sprite);
        explicit Player(sf::Texture const & texture);

        void DoJump(bool const & should_jump);
    };
} // namespace MT


#endif //MOONLIGHT_TRAILS_PLAYER_HPP
