//
// Created by james on 5/15/2020.
//

#include "bhe_core/gameScene.hpp"
#include "Json_Parser.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

std::vector<bhe::entity>
bhe::gameScene::LoadFromJson(const std::string &Json_File,
                             textureManager &Texture_Manager_Out) {
    auto root = bhe::json_parsers::Load(Json_File);

    auto name = root["name"].asString();

  parallaxes_ = bhe::json_parsers::ParseParallax(root["background"],
                                                 Texture_Manager_Out);
  geometry_ = bhe::json_parsers::ParseGeometry(root["geometry"]);
  foreground_decorations_ = bhe::json_parsers::ParseDecorations(
      root["decoration foreground"], Texture_Manager_Out);
  background_decorations_ = bhe::json_parsers::ParseDecorations(
      root["decoration background"], Texture_Manager_Out);

    return bhe::json_parsers::ParseEntities(root["entities"],
                                            Texture_Manager_Out);


}

std::string bhe::gameScene::Name() const { return name_; }

decltype(bhe::gameScene::background_decorations_) const &
bhe::gameScene::BackDecoration() const {
    return background_decorations_;
}

decltype(bhe::gameScene::foreground_decorations_) const &
bhe::gameScene::FrontDecoration() {
    return foreground_decorations_;
}

decltype(bhe::gameScene::geometry_) const &bhe::gameScene::GetCollisionBoxes() {
    return geometry_;
}

decltype(bhe::gameScene::parallaxes_) const &
bhe::gameScene::DoParallax(const sf::Vector2f &Location) {
    for (auto &parallax : parallaxes_) {
        parallax.ApplyParallax(Location);
    }
    return parallaxes_;
}

bhe::gameScene::gameScene(const std::string &Json_File,
                          textureManager &Texture_Manager_Out) {
  LoadFromJson(Json_File, Texture_Manager_Out);
}

bool bhe::gameScene::IsActive() {
    // TODO
    return true;
}
