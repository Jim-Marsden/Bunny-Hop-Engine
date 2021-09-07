//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP

#include <SFML/Graphics.hpp>

namespace bhe {

class Parallax {
protected:
	sf::Sprite sprite;
	float offset{0.0f};
public:
	Parallax() = default;

	~Parallax() = default;

	Parallax(Parallax&&) = default;

	Parallax(Parallax const&) = default;

	Parallax& operator=(Parallax&&) = default;

	Parallax& operator=(Parallax const&) = default;

	explicit Parallax(sf::Texture const& texture, float offset_in = 1);

	sf::Sprite const& get_sprite() const;

	void apply_parallax(sf::Vector2f const& player_speed);

	explicit operator sf::Sprite const&() const;

	explicit operator sf::Drawable const*() const;

};
}// namespace bhe


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PARALLAX_HPP
