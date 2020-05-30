//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_PLAYER_HPP
#define MOONLIGHT_TRAILS_PLAYER_HPP

#include "entity.hpp"

namespace mt {
    class player : public mt::entity {
    protected:
        int jump_count{};
        int jump_timer{};
        int max_jump_timer{5};
        int max_jump_count{2};
    public:
        player() = default;

        explicit player(sf::Sprite const &Sprite);

        explicit player(sf::Texture const &Texture);

        void DoJump(bool const &Should_jump);
    };
} // namespace mt


#endif //MOONLIGHT_TRAILS_PLAYER_HPP
