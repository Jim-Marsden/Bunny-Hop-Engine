//
// Created by james on 5/15/2020.
//

#include "gameScene.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

namespace mt::helper::gamescene {

    Json::Value load_file_to_json(const std::string &Json_file) {
        Json::Value root; // will contain the root value after parsing.
        std::ifstream stream(Json_file, std::ifstream::binary);
        stream >> root;
        return root;
    }

    std::vector<mt::parallax> load_parallax(Json::Value const &Root,
                                            mt::textureManager &Texture_manager) {
        std::vector<mt::parallax> parallaxes;
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
                          mt::textureManager &Texture_manager) {
        std::vector<mt::drawable> foregroundDecorations;

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
                                      mt::textureManager &Texture_manager) {
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

            uint_fast64_t val{};

            for (auto const &animations : entity_value["animation"]) {

                current_entity.AddAnimationState(
                        {animations["name"].asString(),
                         animations["number of frames"].asUInt64(),
                         animations["ticks per frame"].asUInt64(), 0,
                         animations["tick offset"].asUInt64(), ++val});
            }
        }
        return entities;
    }

} // namespace mt::Helper::gameScene

std::vector<mt::entity>
mt::gameScene::LoadFromJson(const std::string &Json_file,
                            textureManager &Texture_manager_out) {
    auto root = mt::helper::gamescene::load_file_to_json(Json_file);

    auto name = root["name"].asString();

    parallaxes = mt::helper::gamescene::load_parallax(root["background"],
                                                      Texture_manager_out);
    geometry = mt::helper::gamescene::load_geometry(root["geometry"]);
    foreground_decorations = mt::helper::gamescene::load_decorations(
            root["decoration foreground"], Texture_manager_out);
    background_decorations = mt::helper::gamescene::load_decorations(
            root["decoration background"], Texture_manager_out);

    return mt::helper::gamescene::load_entities(root["entities"],
                                                Texture_manager_out);
}

std::string mt::gameScene::Name() const { return name; }

decltype(mt::gameScene::background_decorations) const &
mt::gameScene::BackDecoration() const {
    return background_decorations;
}

decltype(mt::gameScene::foreground_decorations) const &
mt::gameScene::FrontDecoration() {
    return foreground_decorations;
}

decltype(mt::gameScene::geometry) const &mt::gameScene::GetCollisionBoxes() {
    return geometry;
}

decltype(mt::gameScene::parallaxes) const &
mt::gameScene::DoParallax(const sf::Vector2f &Location) {
    for (auto &parallax : parallaxes) {
        parallax.ApplyParallax(Location);
    }
    return parallaxes;
}

mt::gameScene::gameScene(const std::string &Json_file,
                         textureManager &Texture_manager_out) {
    LoadFromJson(Json_file, Texture_manager_out);
}

bool mt::gameScene::IsActive() {
    // TODO
    return true;
}
