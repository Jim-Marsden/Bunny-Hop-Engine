//
// Created by james on 5/15/2020.
//

#include "GameScene.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

namespace MT::Helper::GameScene{

    Json::Value LoadFileToJson(const std::string &json_file){
        Json::Value root;   // will contain the root value after parsing.
        std::ifstream stream(json_file, std::ifstream::binary);
        stream >> root;
        return root;
    }
    std::vector<MT::Parallax> LoadParallax(Json::Value const & root, MT::TextureManager & textureManager){
        std::vector<MT::Parallax> parallaxes;
        for(auto const & element : root){
            //textureManager_out.operator+=()
            parallaxes.emplace_back(Parallax(*(textureManager+=element["texture name"].asString()),
                                             element["speed"].asInt()));
        }
        return parallaxes;
    }

    auto LoadGeometry(Json::Value const & root){
        std::vector<sf::RectangleShape> geometry;

        for(auto const & element : root){
            geometry.emplace_back(sf::RectangleShape({element["width"].asFloat(),
                                                      element["height"].asFloat()}));
            geometry.back().setPosition({element["left"].asFloat(),
                                         element["top"].asFloat()});


        }
        return geometry;
    }

    auto LoadDecorations(Json::Value const & root, MT::TextureManager & textureManager) {
        std::vector<MT::Drawable> foreground_decorations;

        for(auto const & element : root){
            foreground_decorations.emplace_back(sf::Sprite(*(textureManager+=element["texture name"].asString())));
            //foreground_decorations.back().set(element["height"].asFloat(), element["width"].asFloat())
            foreground_decorations.back().setPosition(element["left"].asFloat(), element["top"].asFloat());

        }

        return foreground_decorations;

    }

    std::vector<Entity>  LoadEntities(Json::Value const & root, MT::TextureManager & textureManager) {
        std::vector<Entity> entities;
        for (auto const &element : root) {
            Json::Value entity = LoadFileToJson(element["file name"].asString());   // will contain the root value after parsing.
            entities.emplace_back(Entity(*(textureManager += entity["texture name"].asString())));
            auto &current_entity = entities.back();
            current_entity.SetHealth(entity["health"].asInt());
            current_entity.setPosition(element["spawn location"]["left"].asFloat(),element["spawn location"]["top"].asFloat() );
            current_entity.setTextureRect({0, 0,
                                           entity["sprite size"]["h"].asInt(), entity["sprite size"]["w"].asInt()});

            uint_fast64_t val{};

            for(auto const & animations : entity["animation"]) {

                current_entity.AddAnimationState({animations["name"].asString(),
                                                  animations["number of frames"].asUInt64(),
                                                  animations["ticks per frame"].asUInt64(),
                                                  0,animations["tick offset"].asUInt64(), ++val});
            }
        }
        return entities;
    }




    }//MT::Helper::GameScene

std::vector<MT::Entity> MT::GameScene::LoadFromJson(const std::string &json_file, TextureManager &textureManager_out) {
    auto root = MT::Helper::GameScene::LoadFileToJson(json_file);

    auto name = root["name"].asString();

    parallaxes = MT::Helper::GameScene::LoadParallax(root["background"], textureManager_out);
    geometry = MT::Helper::GameScene::LoadGeometry(root["geometry"]);
    foreground_decorations = MT::Helper::GameScene::LoadDecorations(root["decoration foreground"], textureManager_out);
    background_decorations = MT::Helper::GameScene::LoadDecorations(root["decoration background"], textureManager_out);

    return MT::Helper::GameScene::LoadEntities(root["entities"], textureManager_out);
}

std::string MT::GameScene::Name() const {
    return _name;
}

decltype(MT::GameScene::background_decorations)  const &MT::GameScene::BackDecoration() const {
    return background_decorations;
}

decltype(MT::GameScene::foreground_decorations) const &MT::GameScene::FrontDecoration() {
    return foreground_decorations;
}

decltype(MT::GameScene::geometry) const &MT::GameScene::GetCollisionBoxes() {
    return geometry;
}

decltype(MT::GameScene::parallaxes) const &MT::GameScene::DoParallax(const sf::Vector2f &location) {
    for(auto & parallax : parallaxes){
        parallax.ApplyParallax(location);
    }
    return parallaxes;
}

MT::GameScene::GameScene(const std::string &json_file, TextureManager &textureManager_out) {
    LoadFromJson(json_file, textureManager_out);
}

bool MT::GameScene::isActive() {
    //TODO
    return true;
}


