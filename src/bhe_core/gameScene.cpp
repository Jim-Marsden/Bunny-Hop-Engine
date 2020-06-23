//
// Created by james on 5/15/2020.
//

#include "bhe_core/gameScene.hpp"
#include "Json_Parser.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

std::vector<bhe::entity>
bhe::gameScene::LoadFromJson(const std::string &Json_file,
                             textureManager &Texture_manager_out) {
    auto root = bhe::json_parsers::load(Json_file);

    auto name = root["name"].asString();

    _parallaxes = bhe::json_parsers::parse_parallax(root["background"],
                                                        Texture_manager_out);
    _geometry = bhe::json_parsers::parse_geometry(root["geometry"]);
    _foreground_decorations = bhe::json_parsers::parse_decorations(
            root["decoration foreground"], Texture_manager_out);
    _background_decorations = bhe::json_parsers::parse_decorations(
            root["decoration background"], Texture_manager_out);

    return bhe::json_parsers::parse_entities(root["entities"],
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
