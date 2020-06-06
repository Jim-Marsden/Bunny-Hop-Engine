//
// Created by james on 5/15/2020.
//

#include "gameScene.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

namespace bhe::helper::gamescene {

    Json::Value load_file_to_json(const std::string &Json_file) {
        Json::Value root; // will contain the root value after parsing.
        std::ifstream stream(Json_file, std::ifstream::binary);
        stream >> root;
        return root;
    }

    std::vector<bhe::parallax> load_parallax(Json::Value const &Root,
                                             bhe::textureManager &Texture_manager) {
        std::vector<bhe::parallax> parallaxes;
        for (auto const &element : Root) {
            // textureManager_out.operator+=()
            parallaxes.emplace_back(
                    parallax(*(Texture_manager += element["texture name"].asString()),
                             element["speed"].asInt()));
        }
        return parallaxes;
    }

    auto load_geometry(Json::Value const &Root) {
        std::vector<sf::RectangleShape> geometry;

        for (auto const &element : Root) {
            geometry.emplace_back(sf::RectangleShape(
                    {element["width"].asFloat(), element["height"].asFloat()}));
            geometry.back().setPosition(
                    {element["left"].asFloat(), element["top"].asFloat()});
        }
        return geometry;
    }

    auto load_decorations(Json::Value const &Root,
                          bhe::textureManager &Texture_manager) {
        std::vector<bhe::drawable> foregroundDecorations;

        for (auto const &element : Root) {
            foregroundDecorations.emplace_back(
                    sf::Sprite(*(Texture_manager += element["texture name"].asString())));
            // foreground_decorations.back().set(element["height"].asFloat(),
            // element["width"].asFloat())
            foregroundDecorations.back().SetPosition(element["left"].asFloat(),
                                                     element["top"].asFloat());
        }

        return foregroundDecorations;
    }

    std::vector<entity> load_entities(Json::Value const &Root,
                                      bhe::textureManager &Texture_manager) {
        std::vector<entity> entities;
        for (auto const &element : Root) {
            Json::Value entity_value = load_file_to_json(
                    element["file name"]
                            .asString()); // will contain the Root value after parsing.
            entities.emplace_back(
                    entity(*(Texture_manager += entity_value["texture name"].asString())));
            auto &current_entity = entities.back();
            current_entity.SetHealth(entity_value["health"].asInt());
            current_entity.SetPosition(element["spawn location"]["left"].asFloat(),
                                       element["spawn location"]["top"].asFloat());
            current_entity.SetTextureRect({0, 0, entity_value["sprite size"]["h"].asInt(),
                                           entity_value["sprite size"]["w"].asInt()});

            current_entity.SetOrigin(entity_value["sprite size"]["h"].asFloat() / 2.0f,
                                     entity_value["sprite size"]["w"].asFloat() / 2.0f);

            uint_fast64_t val{};

            for (auto const &animations : entity_value["animation"]) {

                current_entity.AddAnimationState(
                        {animations["name"].asString(),
                         animations["number of frames"].asUInt64(),
                         animations["ticks per frame"].asUInt64(), 0,
                         animations["tick offset"].asUInt64(), ++val});
            }
            for (auto const &movement_element : entity_value["movement"]) {
                std::cout << "Movement " << movement_element["name"].asString() << '\t';

                std::cout << "X " << movement_element["speed x"].asFloat() << '\t';
                std::cout << "Y " << movement_element["speed y"].asFloat() << '\t';
                std::cout << "Y " << movement_element["enabled"].asBool() << '\n';

                current_entity.AddMovement(movement_element["name"].asString(),
                                           {movement_element["enabled"].asBool(), movement_element["speed x"].asFloat(),
                                            movement_element["speed y"].asFloat()});

            }
        }
        return entities;
    }

} // namespace bhe::Helper::gameScene

std::vector<bhe::entity>
bhe::gameScene::LoadFromJson(const std::string &Json_file,
                             textureManager &Texture_manager_out) {
    auto root = bhe::helper::gamescene::load_file_to_json(Json_file);

    auto name = root["name"].asString();

    _parallaxes = bhe::helper::gamescene::load_parallax(root["background"],
                                                        Texture_manager_out);
    _geometry = bhe::helper::gamescene::load_geometry(root["geometry"]);
    _foreground_decorations = bhe::helper::gamescene::load_decorations(
            root["decoration foreground"], Texture_manager_out);
    _background_decorations = bhe::helper::gamescene::load_decorations(
            root["decoration background"], Texture_manager_out);

    return bhe::helper::gamescene::load_entities(root["entities"],
                                                 Texture_manager_out);
}

std::string bhe::gameScene::Name() const { return _name; }

decltype(bhe::gameScene::_background_decorations) const &
bhe::gameScene::BackDecoration() const {
    return _background_decorations;
}

decltype(bhe::gameScene::_foreground_decorations) const &
bhe::gameScene::FrontDecoration() {
    return _foreground_decorations;
}

decltype(bhe::gameScene::_geometry) const &bhe::gameScene::GetCollisionBoxes() {
    return _geometry;
}

decltype(bhe::gameScene::_parallaxes) const &
bhe::gameScene::DoParallax(const sf::Vector2f &Location) {
    for (auto &parallax : _parallaxes) {
        parallax.ApplyParallax(Location);
    }
    return _parallaxes;
}

bhe::gameScene::gameScene(const std::string &Json_file,
                          textureManager &Texture_manager_out) {
    LoadFromJson(Json_file, Texture_manager_out);
}

bool bhe::gameScene::IsActive() {
    // TODO
    return true;
}
