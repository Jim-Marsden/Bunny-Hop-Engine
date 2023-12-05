//
// Created by snizzfox on 5/30/20.
//

#include <fstream>
#include <bhe_core/Json_Parser.hpp>
#include <iostream>
#include <chrono>

#include <fmt/format.h>

// #include <json/json.h>

#include "entity.hpp"

namespace bhe::json_parsers::helpers
{
	[[nodiscard]] auto parse_movement(json_t const& Root)
	{
		struct result
		{
			std::string key;
			bhe::Movement::movementDataT value;
		};

		std::string name = Root.at("name");
		bool enabled = Root.at("enabled");
		float x = Root.at("speed x");
		float y = Root.at("speed y");

		fmt::println("name: {}, enabled: {}, x: {}, y: {}",name,  enabled, x, y);
		bool has_timer = Root.at("has timer");
		int timer{};
		int max_timer{};

		if(has_timer)
		{
			timer = Root.at("timer");
			max_timer = Root.at("max timer");
		}


		return result{
			name, {
				enabled, ///Root["enabled"],
				x,
				y,
				has_timer,
				 timer,
				max_timer}};
	}
}

auto bhe::json_parsers::jp_v0_0_0::load(std::string const& json_file) -> json_t
{
	json_t json{};
	std::ifstream(json_file) >> json;
	return json;
}

auto bhe::json_parsers::jp_v0_0_0::parse_parallax(json_t const& root,
                                       bhe::textureManager& texture_manager) -> std::vector<bhe::Parallax>
{
	std::vector<bhe::Parallax> parallaxes;
	for (auto const& element : root)
	{
		// textureManager_out.operator+=()
		parallaxes.emplace_back(
			Parallax(*(texture_manager += element["texture name"]),
			         element["speed"]));
	}
	return parallaxes;
}

auto bhe::json_parsers::jp_v0_0_0::parse_geometry(json_t const& root) -> std::vector<sf::RectangleShape>
{
	std::vector<sf::RectangleShape> geometry;

	for (auto const& element : root)
	{
		geometry.emplace_back(sf::RectangleShape(
			{element["width"], element["height"]}));
		geometry.back().setPosition(
			{element["left"], element["top"]});
	}
	return geometry;
}

auto bhe::json_parsers::jp_v0_0_0::parse_decorations(json_t const& root,
                                          bhe::textureManager& texture_manager) -> std::vector<bhe::Drawable>
{
	std::vector<bhe::Drawable> decorations;

	for (auto const& element : root)
	{
		decorations.emplace_back(
			sf::Sprite(*(texture_manager += element["texture name"])));
		// foreground_decorations.back().set(element["height"].asFloat(),
		// element["width"].asFloat())
		decorations.back().set_position(element["left"],
		                                element["top"]);
	}

	return decorations;
}

auto bhe::json_parsers::jp_v0_0_0::parse_entity(json_t const& root, bhe::textureManager& texture_manager) -> bhe::Entity
{
	auto entity_value = load(
		root["file get_name"]);

	bhe::Entity result_entity(*(texture_manager += entity_value["texture get_name"]));

	result_entity.set_health(entity_value["health"]);
	result_entity.set_position(root["spawn location"]["left"],
	                           root["spawn location"]["top"]);
	result_entity.set_texture_rect({
		{0, 0}, {
			entity_value["sprite size"]["h"],
			entity_value["sprite size"]["w"]
		}
	});

	result_entity.set_origin(static_cast<float>(entity_value["sprite size"]["h"]) / 2.0f,
	                         static_cast<float>(entity_value["sprite size"]["w"]) / 2.0f);

	for (auto const& animations : entity_value["animation"])
	{
		std::cout << animations["time per frame"] << '\n';

		result_entity.add_animation_state({
			animations["get_name"],
			animations["number of frames"],
			animations["animation offset"],
			animations["time per frame"]
		});
	}
	for (auto const& movement_element : entity_value["movement"])
	{
		auto [key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result_entity.add_movement(key, value);
	}
	return result_entity;
}

auto
bhe::json_parsers::jp_v0_0_0::load_entity(std::string const& file_name, bhe::textureManager& texture_manager) -> bhe::Entity
{
	auto entity_value = bhe::json_parsers::load(file_name);

	bhe::Entity result_entity(*(texture_manager += entity_value["texture name"]));

	result_entity.set_health(entity_value["health"]);

	result_entity.set_texture_rect({
		{0, 0}, {
			entity_value["sprite size"]["h"],
			entity_value["sprite size"]["w"]
		}
	});

	result_entity.set_origin(static_cast<float>(entity_value["sprite size"]["h"]) / 2.0f,
	                         static_cast<float>(entity_value["sprite size"]["w"]) / 2.0f);

	for (auto const& animations : entity_value["animation"])
	{
		std::chrono::duration<float> fsec(animations["time per frame"]);

		long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
		std::cout << grumpy << '\n';

		result_entity.add_animation_state({
			animations["name"],
			animations["number of frames"],
			animations["animation offset"],
			grumpy
		});
	}
	for (auto const& movement_element : entity_value["movement"])
	{
		auto [key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result_entity.add_movement(key, value);
	}
	return result_entity;
}

auto bhe::json_parsers::jp_v0_0_0::parse_entities(json_t const& Root,
                                       bhe::textureManager& texture_manager) -> std::vector<bhe::Entity>
{
	std::vector<bhe::Entity> local_entities;
	for (auto const& element : Root)
	{
		//std::cout << element["file get_name"].asString() << '\n';
		//auto temp = load( element["file get_name"].asString());
		local_entities
			.push_back(bhe::json_parsers::load_entity(element["file name"], texture_manager));

		//local_entities.push_back(parse_entity(load( element["file get_name"].asString()), Texture_manager));
		local_entities.back()
		              .set_position(element["spawn location"]["top"], element["spawn location"]["left"]);
	}
	return local_entities;
}

auto
bhe::json_parsers::jp_v0_0_0::parse_player(std::string_view const& file_name,
                                bhe::textureManager& texture_manager) -> bhe::player
{
	auto root = bhe::json_parsers::load(std::string(file_name));

	bhe::player result(*(texture_manager += root["texture name"]));
	result.set_texture_rect({{0, 0}, {root["sprite size"]["w"], root["sprite size"]["h"]}});

	result.set_health(root["health"]);

	result.set_origin(static_cast<float>(root["sprite size"]["w"]) / 2.f,
	                  static_cast<float>(root["sprite size"]["h"]) / 2.f);

	uint_fast64_t val{};

	for (auto const& animations : root["animation"])
	{
		std::chrono::duration<float> fsec(animations["time per frame"]);

		long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
		std::cout << grumpy << '\n';

		if (root.empty()) throw std::runtime_error("Json is empty?");
		std::string animation_name = "asdf"; //animations["get_name"];
		unsigned long long numb_of_frames = animations["number of frames"];

		unsigned long long animation_offset = animations["animation offset"];
		// result.add_animation_state({animation_name, numb_of_frames, animation_offset, grumpy});

		result.add_animation_state({
			animations["name"],
			animations["number of frames"],
			animations["animation offset"],
			grumpy
		});

		//result.add_animation_state({animations["get_name"].asString(), animations["number of frames"].asUInt64(), animations["animation offset"].asUInt64(),
		// animations["time per frame"].asFloat()});
	}

	for (auto const& movement_element : root["movement"])
	{
		auto [key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
		result.add_movement(key, value);
		std::cout << "Player movment :" << key << '\t' << value.x << ":" << value.y << '\n';
	}

	return result;
}
