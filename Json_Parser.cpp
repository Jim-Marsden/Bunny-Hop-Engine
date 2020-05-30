//
// Created by snizzfox on 5/30/20.
//

#include <fstream>
#include "Json_Parser.hpp"
#include <json/json.h>
#include <entities.h>


auto mt::json_parsers::load(std::string const &Json_file) -> Json::Value {
    Json::Value root; // will contain the root value after parsing.
    std::ifstream stream(Json_file, std::ifstream::binary);
    stream >> root;
    return root;
}

auto mt::json_parsers::parse_parallax(Json::Value const &Root,
                                      mt::textureManager &Texture_manager) -> std::vector<mt::parallax> {
    std::vector<mt::parallax> parallaxes;
    for (auto const &element : Root) {
        // textureManager_out.operator+=()
        parallaxes.emplace_back(
                parallax(*(Texture_manager += element["texture name"].asString()),
                         element["speed"].asInt()));
    }
    return parallaxes;
}

auto mt::json_parsers::parse_geometry(Json::Value const &Root) -> std::vector<sf::RectangleShape> {
    std::vector<sf::RectangleShape> geometry;

    for (auto const &element : Root) {
        geometry.emplace_back(sf::RectangleShape(
                {element["width"].asFloat(), element["height"].asFloat()}));
        geometry.back().setPosition(
                {element["left"].asFloat(), element["top"].asFloat()});
    }
    return geometry;
}

auto mt::json_parsers::load_decorations(Json::Value const &Root,
                                        mt::textureManager &Texture_manager) -> std::vector<mt::drawable> {
    std::vector<mt::drawable> decorations;

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

auto mt::json_parsers::parse_entity(Json::Value const &Root, mt::textureManager &Texture_manager) -> mt::entity {
    auto entity_value = load(
            Root["file name"]
                    .asString());

    mt::entity result_entity(*(Texture_manager += entity_value["texture name"].asString()));


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


        result_entity.AddMovement(movement_element["name"].asString(),
                                  {movement_element["enabled"].asBool(), movement_element["speed x"].asFloat(),
                                   movement_element["speed y"].asFloat()});

    }
    return result_entity;
}

auto mt::json_parsers::parse_entities(Json::Value const &Root,
                                      mt::textureManager &Texture_manager) -> std::vector<mt::entity> {
    std::vector<mt::entity> local_entities;
    for (auto const &element : Root) {
        local_entities.push_back(parse_entity(element, Texture_manager));
    }
    return local_entities;
}

auto
mt::json_parsers::parse_player(std::string_view const &File_name, mt::textureManager &Texture_manager) -> mt::player {


    auto root = mt::json_parsers::load(std::string(File_name));

    mt::player result(*(Texture_manager += root["texture name"].asString()));
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
        result.AddMovement(movement_element["name"].asString(),
                           {movement_element["enabled"].asBool(), movement_element["speed x"].asFloat(),
                            movement_element["speed y"].asFloat()});

    }


    return result;
}
