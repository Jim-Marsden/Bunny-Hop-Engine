//
// Created by snizzfox on 5/30/20.
//

#include <fstream>
#include <bhe_core/Json_Parser.hpp>
#include <json/json.h>
#include "entity.hpp"

namespace bhe::json_parsers::helpers {
    [[nodiscard]] auto parse_movement(Json::Value const &Root) {

        struct result {
            std::string key;
            bhe::movement::movementDataT value;
        };
        return result{Root["name"].asString(), {Root["enabled"].asBool(),
                                                Root["speed x"].asFloat(),
                                                Root["speed y"].asFloat(),
                                                Root["has timer"].asBool(),
                                                Root["has timer"].asBool() ? Root["timer"].asInt() : 0,
                                                Root["has timer"].asBool() ? Root["timer"].asInt() : 0}};

    }


}

auto bhe::json_parsers::load(std::string const &Json_file) -> Json::Value {
    Json::Value root; // will contain the root value after parsing.
    std::ifstream stream(Json_file, std::ifstream::binary);
    stream >> root;
    return root;
}

auto bhe::json_parsers::parse_parallax(Json::Value const &Root,
                                       bhe::textureManager &Texture_manager) -> std::vector<bhe::parallax> {
    std::vector<bhe::parallax> parallaxes;
    for (auto const &element : Root) {
        // textureManager_out.operator+=()
        parallaxes.emplace_back(
                parallax(*(Texture_manager += element["texture name"].asString()),
                         element["speed"].asInt()));
    }
    return parallaxes;
}

auto bhe::json_parsers::parse_geometry(Json::Value const &Root) -> std::vector<sf::RectangleShape> {
    std::vector<sf::RectangleShape> geometry;

    for (auto const &element : Root) {
        geometry.emplace_back(sf::RectangleShape(
                {element["width"].asFloat(), element["height"].asFloat()}));
        geometry.back().setPosition(
                {element["left"].asFloat(), element["top"].asFloat()});
    }
    return geometry;
}

auto bhe::json_parsers::load_decorations(Json::Value const &Root,
                                         bhe::textureManager &Texture_manager) -> std::vector<bhe::drawable> {
    std::vector<bhe::drawable> decorations;

    for (auto const &element : Root) {
        decorations.emplace_back(
                sf::Sprite(*(Texture_manager += element["texture name"].asString())));
        // foreground_decorations.back().set(element["height"].asFloat(),
        // element["width"].asFloat())
        decorations.back().SetPosition(element["left"].asFloat(),
                                       element["top"].asFloat());
    }

    return decorations;
}

auto bhe::json_parsers::parse_entity(Json::Value const &Root, bhe::textureManager &Texture_manager) -> bhe::entity {
    auto entity_value = load(
            Root["file name"]
                    .asString());

    bhe::entity result_entity(*(Texture_manager += entity_value["texture name"].asString()));


    result_entity.SetHealth(entity_value["health"].asInt());
    result_entity.SetPosition(Root["spawn location"]["left"].asFloat(),
                              Root["spawn location"]["top"].asFloat());
    result_entity.SetTextureRect({0, 0, entity_value["sprite size"]["h"].asInt(),
                                  entity_value["sprite size"]["w"].asInt()});

    result_entity.SetOrigin(entity_value["sprite size"]["h"].asFloat() / 2.0f,
                            entity_value["sprite size"]["w"].asFloat() / 2.0f);

    uint_fast64_t val{};

    for (auto const &animations : entity_value["animation"]) {

        result_entity.AddAnimationState(
                {animations["name"].asString(),
                 animations["number of frames"].asUInt64(),
                 animations["ticks per frame"].asUInt64(), 0,
                 animations["tick offset"].asUInt64(), ++val});
    }
    for (auto const &movement_element : entity_value["movement"]) {
        auto[key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
        result_entity.AddMovement(key, value);
    }
    return result_entity;
}

auto bhe::json_parsers::parse_entities(Json::Value const &Root,
                                       bhe::textureManager &Texture_manager) -> std::vector<bhe::entity> {
    std::vector<bhe::entity> local_entities;
    for (auto const &element : Root) {
        local_entities.push_back(parse_entity(element, Texture_manager));
    }
    return local_entities;
}

auto
bhe::json_parsers::parse_player(std::string_view const &File_name,
                                bhe::textureManager &Texture_manager) -> bhe::player {


    auto root = bhe::json_parsers::load(std::string(File_name));

    bhe::player result(*(Texture_manager += root["texture name"].asString()));
    result.SetTextureRect({0, 0, root["sprite size"]["w"].asInt(), root["sprite size"]["h"].asInt()});

    result.SetHealth(root["health"].asInt());

    result.SetOrigin(root["sprite size"]["w"].asFloat() / 2.f, root["sprite size"]["h"].asFloat() / 2.f);


    uint_fast64_t val{};


    for (auto const &animations : root["animation"]) {

        result.AddAnimationState(
                {animations["name"].asString(),
                 animations["number of frames"].asUInt64(),
                 animations["ticks per frame"].asUInt64(), 0,
                 animations["tick offset"].asUInt64(), ++val});
    }

    for (auto const &movement_element : root["movement"]) {
        auto[key, value] = bhe::json_parsers::helpers::parse_movement(movement_element);
        result.AddMovement(key, value);
    }


    return result;
}
