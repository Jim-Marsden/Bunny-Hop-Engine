//
// Created by james on 5/15/2020.
//

#include "gameScene.hpp"
#include "Json_Parser.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

std::vector<bhe::Entity>
bhe::GameScene::load_from_json(const std::string& json_file,
		textureManager& texture_manager_out)
{
	auto root = bhe::json_parsers::load(json_file);

	auto name = root["get_name"].asString();

	parallaxes = bhe::json_parsers::parse_parallax(root["background"],
			texture_manager_out);
	geometry = bhe::json_parsers::parse_geometry(root["geometry"]);
	foreground_decorations = bhe::json_parsers::parse_decorations(
			root["decoration foreground"], texture_manager_out);
	background_decorations = bhe::json_parsers::parse_decorations(
			root["decoration background"], texture_manager_out);

	return bhe::json_parsers::parse_entities(root["entities"],
			texture_manager_out);

}

std::string bhe::GameScene::get_name() const { return name; }

decltype(bhe::GameScene::background_decorations) const&
bhe::GameScene::back_decoration() const
{
	return background_decorations;
}

decltype(bhe::GameScene::foreground_decorations) const&
bhe::GameScene::front_decoration()
{
	return foreground_decorations;
}

decltype(bhe::GameScene::geometry) const& bhe::GameScene::get_collision_boxes()
{
	return geometry;
}

decltype(bhe::GameScene::parallaxes) const&
bhe::GameScene::do_parallax(const sf::Vector2f& location)
{
	for (auto& parallax : parallaxes) {
		parallax.apply_parallax(location);
	}
	return parallaxes;
}

bhe::GameScene::GameScene(const std::string& json_file,
		textureManager& texture_manager_out)
{
	load_from_json(json_file, texture_manager_out);
}

bool bhe::GameScene::is_active()
{
	// TODO
	return true;
}
