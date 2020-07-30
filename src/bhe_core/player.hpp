//
// Created by snizzfox on 5/16/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PLAYER_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PLAYER_HPP

#include <bhe_core/entity.hpp>
#include <bhe_core/textureManager.hpp>

namespace bhe {
    class player : public bhe::entity {
    protected:
        int jump_count_{};
        int jump_timer_{};
        int max_jump_timer_{5};
        int max_jump_count_{2};
    public:
        explicit player(sf::Sprite const &Sprite);

        explicit player(sf::Texture const &Texture);

        void DoJump(bool const &Should_Jump);

        void MoveLeft(bool const &Should_Jump);

        void MoveRight(bool const &Should_Jump);

        void MoveDown(bool const &Should_Jump);

        [[nodiscard]] sf::Vector2f GetPos() const;
    };


} // namespace bhe


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PLAYER_HPP
