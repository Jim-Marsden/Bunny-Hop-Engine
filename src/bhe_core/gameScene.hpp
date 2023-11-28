//
// Created by james on 5/15/2020.
//

#pragma once

#include "textureManager.hpp"
#include "parallax.hpp"
#include "drawable.hpp"
#include "entity.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace bhe {
class GameScene {
	std::string name;

	//TODO parallax class
	std::vector<Parallax> parallaxes;
	std::vector<sf::RectangleShape> geometry;
	std::vector<bhe::Drawable> background_decorations;
	std::vector<bhe::Drawable> foreground_decorations;

public:
	GameScene() = default;

	~GameScene() = default;

	GameScene(GameScene const&) = default;

	GameScene(GameScene&&) = default;

	GameScene& operator=(GameScene&&) = default;

	GameScene& operator=(GameScene const&) = default;

	GameScene(std::string const& json_file, textureManager& texture_manager_out);

	[[nodiscard]]decltype(parallaxes) const& do_parallax(sf::Vector2f const& location);

	[[nodiscard]] decltype(geometry) const& get_collision_boxes();

	[[nodiscard]]decltype(foreground_decorations) const& front_decoration();

	[[nodiscard]]decltype(background_decorations) const& back_decoration() const;

	[[nodiscard]] std::string get_name() const;

	std::vector<Entity> load_from_json(std::string const& json_file, textureManager& texture_manager_out);

	static bool is_active();
};

} //namespace bhe
