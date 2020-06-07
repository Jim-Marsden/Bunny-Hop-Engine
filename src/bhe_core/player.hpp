//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_PLAYER_HPP
#define MOONLIGHT_TRAILS_PLAYER_HPP

#include "entity.hpp"
#include "textureManager.hpp"


namespace bhe {
    class player : public bhe::entity {
    protected:
        int _jump_count{};
        int _jump_timer{};
        int _max_jump_timer{5};
        int _max_jump_count{2};
    public:
        explicit player(sf::Sprite const &Sprite);

        explicit player(sf::Texture const &Texture);

        void DoJump(bool const &Should_jump);

        void MoveLeft(bool const &Should_jump);

        void MoveRight(bool const &Should_jump);

        void MoveDown(bool const &Should_jump);

        [[nodiscard]] sf::Vector2f GetPos() const;
    };


} // namespace bhe


#endif //MOONLIGHT_TRAILS_PLAYER_HPP
