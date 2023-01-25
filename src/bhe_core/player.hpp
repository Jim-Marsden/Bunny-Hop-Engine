//
// Created by snizzfox on 5/16/20.
//

#pragma once

#include "bhe_core/entity.hpp"
#include "bhe_core/textureManager.hpp"

namespace bhe {
class player: public bhe::Entity {
protected:
	int jump_count{};
	int jump_timer{};
	int max_jump_timer{5};
	int max_jump_count{2};
public:
	explicit player(sf::Sprite const& sprite);

	explicit player(sf::Texture const& texture);

	void do_jump(bool const& should_jump);

	void move_left(bool const& should_jump);

	void move_right(bool const& should_jump);

	void move_down(bool const& should_jump);

	[[nodiscard]] sf::Vector2f get_pos() const;
};

} // namespace bhe
