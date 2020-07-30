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
    [[nodiscard]] auto ParseMovement(Json::Value const &Root) {

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

auto bhe::json_parsers::Load(std::string const &Json_File) -> Json::Value {
    Json::Value root; // will contain the root value after parsing.
    std::ifstream stream(Json_File, std::ifstream::binary);
    stream >> root;
    return root;
}

auto bhe::json_parsers::ParseParallax(Json::Value const &Root,
                                      bhe::textureManager &Texture_Manager) -> std::vector<bhe::parallax> {
    std::vector<bhe::parallax> parallaxes;
    for (auto const &element : Root) {
        // textureManager_out.operator+=()
        parallaxes.emplace_back(
                parallax(*(Texture_Manager += element["texture name"].asString()),
                         element["speed"].asInt()));
    }
    return parallaxes;
}

auto bhe::json_parsers::ParseGeometry(Json::Value const &Root) -> std::vector<sf::RectangleShape> {
    std::vector<sf::RectangleShape> geometry;

    for (auto const &element : Root) {
        geometry.emplace_back(sf::RectangleShape(
                {element["width"].asFloat(), element["height"].asFloat()}));
        geometry.back().setPosition(
                {element["left"].asFloat(), element["top"].asFloat()});
    }
    return geometry;
}

auto bhe::json_parsers::ParseDecorations(Json::Value const &Root,
                                         bhe::textureManager &Texture_Manager) -> std::vector<bhe::drawable> {
    std::vector<bhe::drawable> decorations;

    for (auto const &element : Root) {
        decorations.emplace_back(
                sf::Sprite(*(Texture_Manager += element["texture name"].asString())));
        // foreground_decorations.back().set(element["height"].asFloat(),
        // element["width"].asFloat())
        decorations.back().SetPosition(element["left"].asFloat(),
                                       element["top"].asFloat());
    }

    return decorations;
}

auto bhe::json_parsers::ParseEntity(Json::Value const &Root, bhe::textureManager &Texture_Manager) -> bhe::entity {
    auto entity_value = Load(
        Root["file name"]
            .asString());

    bhe::entity result_entity(*(Texture_Manager += entity_value["texture name"].asString()));


    result_entity.SetHealth(entity_value["health"].asInt());
    result_entity.SetPosition(Root["spawn location"]["left"].asFloat(),
                              Root["spawn location"]["top"].asFloat());
    result_entity.SetTextureRect({0, 0, entity_value["sprite size"]["h"].asInt(),
                                  entity_value["sprite size"]["w"].asInt()});

    result_entity.SetOrigin(entity_value["sprite size"]["h"].asFloat() / 2.0f,
                            entity_value["sprite size"]["w"].asFloat() / 2.0f);

    for (auto const &animations : entity_value["animation"]) {
        std::cout << animations["time per frame"].asFloat() << '\n';

        result_entity.AddAnimationState({animations["name"].asString(),
                                         animations["number of frames"].asUInt64(),
                                         animations["animation offset"].asUInt64(),
        animations["time per frame"].asInt()});
    }
    for (auto const &movement_element : entity_value["movement"]) {
        auto[key, value] = bhe::json_parsers::helpers::ParseMovement(movement_element);
        result_entity.AddMovement(key, value);
    }
    return result_entity;
}

auto
bhe::json_parsers::LoadEntity(std::string const & File_Name, bhe::textureManager &Texture_Manager) -> bhe::entity{
    auto entity_value = bhe::json_parsers::Load(File_Name);

    bhe::entity result_entity(*(Texture_Manager += entity_value["texture name"].asString()));


    result_entity.SetHealth(entity_value["health"].asInt());

    result_entity.SetTextureRect({0, 0, entity_value["sprite size"]["h"].asInt(),
                                  entity_value["sprite size"]["w"].asInt()});

    result_entity.SetOrigin(entity_value["sprite size"]["h"].asFloat() / 2.0f,
                            entity_value["sprite size"]["w"].asFloat() / 2.0f);

    for (auto const &animations : entity_value["animation"]) {

        std::chrono::duration<float> fsec(animations["time per frame"].asDouble());


        long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
        std::cout << grumpy << '\n';


        result_entity.AddAnimationState({animations["name"].asString(),
                                         animations["number of frames"].asUInt64(),
                                         animations["animation offset"].asUInt64(),
                                         grumpy});
    }
    for (auto const &movement_element : entity_value["movement"]) {
        auto[key, value] = bhe::json_parsers::helpers::ParseMovement(movement_element);
        result_entity.AddMovement(key, value);
    }
    return result_entity;
}


auto bhe::json_parsers::ParseEntities(Json::Value const &Root,
                                      bhe::textureManager &Texture_Manager) -> std::vector<bhe::entity> {
    std::vector<bhe::entity> local_entities;
    for (auto const &element : Root) {
        //std::cout << element["file name"].asString() << '\n';
        //auto temp = Load( element["file name"].asString());
        local_entities.emplace_back(bhe::json_parsers::LoadEntity(element["file name"].asString(), Texture_Manager));

        //local_entities.push_back(ParseEntity(Load( element["file name"].asString()), Texture_manager));
        local_entities.back().SetPosition(element["spawn location"]["top"].asFloat(), element["spawn location"]["left"].asFloat());
    }
    return local_entities;
}

auto
bhe::json_parsers::ParsePlayer(std::string_view const &File_Name,
                               bhe::textureManager &Texture_Manager) -> bhe::player {


    auto root = bhe::json_parsers::Load(std::string(File_Name));

    bhe::player result(*(Texture_Manager += root["texture name"].asString()));
    result.SetTextureRect({0, 0, root["sprite size"]["w"].asInt(), root["sprite size"]["h"].asInt()});

    result.SetHealth(root["health"].asInt());

    result.SetOrigin(root["sprite size"]["w"].asFloat() / 2.f, root["sprite size"]["h"].asFloat() / 2.f);


    uint_fast64_t val{};


    for (auto const &animations : root["animation"]) {

        std::chrono::duration<float> fsec(animations["time per frame"].asDouble());


        long grumpy = std::chrono::duration_cast<std::chrono::microseconds>(fsec).count();
        std::cout << grumpy << '\n';


        result.AddAnimationState({animations["name"].asString(),
                                  animations["number of frames"].asUInt64(),
                                  animations["animation offset"].asUInt64(),
                                  grumpy});

        //result.AddAnimationState({animations["name"].asString(), animations["number of frames"].asUInt64(), animations["animation offset"].asUInt64(),
        // animations["time per frame"].asFloat()});
    }

    for (auto const &movement_element : root["movement"]) {
        auto[key, value] = bhe::json_parsers::helpers::ParseMovement(movement_element);
        result.AddMovement(key, value);
    }


    return result;
}
