//
// Created by snizzfox on 5/30/20.
//

#include <fstream>
#include <bhe_core/Json_Parser.hpp>
#include <json/json.h>
#include <iostream>
#include <chrono>

#include "entity.hpp"

namespace bhe::json_parsers::helpers {
[[nodiscard]] auto parse_movement(Json::Value const& Root)
{

	struct result {
		std::string key;
		bhe::Movement::movementDataT value;
	};
	return result{Root["name"].asString(), {Root["enabled"].asBool(),
												Root["speed x"].asFloat(),
												Root["speed y"].asFloat(),
												Root["has timer"].asBool(),
												Root["has timer"].asBool() ? Root["timer"].asInt() : 0,
												Root["has timer"].asBool() ? Root["timer"].asInt() : 0}};

}

}

auto bhe::json_parsers::load(std::string const& json_file) -> Json::Value
{
	Json::Value root; // will contain the root value after parsing.
	std::ifstream stream(json_file, std::ifstream::binary);
	stream >> root;
	return root;
}

auto bhe::json_parsers::parse_parallax(Json::Value const& root,
		bhe::textureManager& texture_manager) -> std::vector<bhe::Parallax>
{
	std::vector<bhe::Parallax> parallaxes;
	for (auto const& element : root) {
		// textureManager_out.operator+=()
		parallaxes.emplace_back(
				Parallax(*(texture_manager += element["texture name"].asString()),
						element["speed"].asInt()));
	}
	return parallaxes;
}

auto bhe::json_parsers::parse_geometry(Json::Value const& root) -> std::vector<sf::RectangleShape>
{
	std::vector<sf::RectangleShape> geometry;

	for (auto const& element : root) {
		geometry.emplace_back(sf::RectangleShape(
				{element["width"].asFloat(), element["height"].asFloat()}));
		geometry.back().setPosition(
				{element["left"].asFloat(), element["top"].asFloat()});
	}
	return geometry;
}

auto bhe::json_parsers::parse_decorations(Json::Value const& root,
		bhe::textureManager& texture_manager) -> std::vector<bhe::Drawable>
{
	std::vector<bhe::Drawable> decorations;

	for (auto const& element : root) {
		decorations.emplace_back(
				sf::Sprite(*(texture_manager += element["texture name"].asString())));
		// foreground_decorations.back().set(element["height"].asFloat(),
		// element["width"].asFloat())
		decorations.back().set_position(element["left"].asFloat(),
				element["top"].asFloat());
	}

	return decorations;
}

auto bhe::json_parsers::parse_entity(Json::Value const& root, bhe::textureManager& texture_manager) -> bhe::Entity
{
	auto entity_value = load(
			root["file get_name"]
					.asString());

	bhe::Entity result_entity(*(texture_manager += entity_value["texture get_name"].asString()));

	result_entity.set_health(entity_value["health"].asInt());
	result_entity.set_position(root["spawn location"]["left"].asFloat(),
			root["spawn location"]["top"].asFloat());
	result_entity.set_texture_rect({0, 0, entity_value["sprite size"]["h"].asInt(),
									entity_value["sprite size"]["w"].asInt()});

	result_entity.set_origin(entity_value["sprite size"]["h"].asFloat()/2.0f,
			entity_value["sprite size"]["w"].asFloat()/2.0f);

	for (auto const& animations : entity_value["animation"]) {
		std::cout << animations["time per frame"].asFloat() << '\n';

		result_entity.add_animation_state({animations["get_name"].asString(),
										   animations["number of frames"].asUInt64(),
										   animations["animation offset"].asUInt64(),
										   animations["time per frame"].asInt()});
	}
	for (auto const& movement_element : entity_value["movement"]) {
		auto[key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result_entity.add_movement(key, value);
	}
	return result_entity;
}

auto
bhe::json_parsers::load_entity(std::string const& file_name, bhe::textureManager& texture_manager) -> bhe::Entity
{
	auto entity_value = bhe::json_parsers::load(file_name);

	bhe::Entity result_entity(*(texture_manager += entity_value["texture name"].asString()));

	result_entity.set_health(entity_value["health"].asInt());

	result_entity.set_texture_rect({0, 0, entity_value["sprite size"]["h"].asInt(),
									entity_value["sprite size"]["w"].asInt()});

	result_entity.set_origin(entity_value["sprite size"]["h"].asFloat()/2.0f,
			entity_value["sprite size"]["w"].asFloat()/2.0f);

	for (auto const& animations : entity_value["animation"]) {

		std::chrono::duration<float> fsec(animations["time per frame"].asDouble());

		long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
		std::cout << grumpy << '\n';

		result_entity.add_animation_state({animations["get_name"].asString(),
										   animations["number of frames"].asUInt64(),
										   animations["animation offset"].asUInt64(),
										   grumpy});
	}
	for (auto const& movement_element : entity_value["movement"]) {
		auto[key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result_entity.add_movement(key, value);
	}
	return result_entity;
}

auto bhe::json_parsers::parse_entities(Json::Value const& Root,
		bhe::textureManager& texture_manager) -> std::vector<bhe::Entity>
{
	std::vector<bhe::Entity> local_entities;
	for (auto const& element : Root) {
		//std::cout << element["file get_name"].asString() << '\n';
		//auto temp = load( element["file get_name"].asString());
		local_entities
				.emplace_back(bhe::json_parsers::load_entity(element["file name"].asString(), texture_manager));

		//local_entities.push_back(parse_entity(load( element["file get_name"].asString()), Texture_manager));
		local_entities.back()
				.set_position(element["spawn location"]["top"].asFloat(), element["spawn location"]["left"].asFloat());
	}
	return local_entities;
}

auto
bhe::json_parsers::parse_player(std::string_view const& file_name,
		bhe::textureManager& texture_manager) -> bhe::player
{

	auto root = bhe::json_parsers::load(std::string(file_name));

	bhe::player result(*(texture_manager += root["texture name"].asString()));
	result.set_texture_rect({0, 0, root["sprite size"]["w"].asInt(), root["sprite size"]["h"].asInt()});

	result.set_health(root["health"].asInt());

	result.set_origin(root["sprite size"]["w"].asFloat()/2.f, root["sprite size"]["h"].asFloat()/2.f);

	uint_fast64_t val{};

	for (auto const& animations : root["animation"]) {

		std::chrono::duration<float> fsec(animations["time per frame"].asDouble());

		long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
		std::cout << grumpy << '\n';

		result.add_animation_state({animations["get_name"].asString(),
									animations["number of frames"].asUInt64(),
									animations["animation offset"].asUInt64(),
									grumpy});

		//result.add_animation_state({animations["get_name"].asString(), animations["number of frames"].asUInt64(), animations["animation offset"].asUInt64(),
		// animations["time per frame"].asFloat()});
	}

	for (auto const& movement_element : root["movement"]) {
		auto[key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result.add_movement(key, value);
		std::cout << "Player movment :" << key << '\t' << value.x << ":" << value.y << '\n';
	}

	return result;
}
