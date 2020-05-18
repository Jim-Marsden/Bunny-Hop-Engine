//
// Created by james on 5/15/2020.
//

#include "GameScene.hpp"
#include <json/json.h>

#include <fstream>
#include <iostream>

std::vector<MT::Entity> GameScene::LoadFromJson(const std::string &json_file, TextureManager &textureManager_out) {
    Json::Value root;   // will contain the root value after parsing.
    std::ifstream stream(json_file, std::ifstream::binary);
    stream >> root;

    std::string name = root["name"].asString();

    auto backgrounds = root["background"];
    for(auto const & element : backgrounds){
        //textureManager_out.operator+=()
        parallaxes.emplace_back(Parallax(*(textureManager_out+=element["texture name"].asString()),
                element["speed"].asInt()));
    }

    //auto geometry = root["geometry"];
    for(auto const & element : root["geometry"]){
        geometry.emplace_back(sf::RectangleShape({element["width"].asFloat(),
                                                  element["height"].asFloat()}));
        geometry.back().setPosition({element["left"].asFloat(),
                                     element["top"].asFloat()});


    }

    for(auto const & element : root["decoration foreground"]){
        foreground_decorations.emplace_back(sf::Sprite(*(textureManager_out+=element["texture name"].asString())));
        //foreground_decorations.back().set(element["height"].asFloat(), element["width"].asFloat())
        foreground_decorations.back().setPosition(element["left"].asFloat(), element["top"].asFloat());

    }

    for(auto const & element : root["decoration background"]){
        background_decorations.emplace_back(sf::Sprite(*(textureManager_out+=element["texture name"].asString())));
        //foreground_decorations.back().set(element["height"].asFloat(), element["width"].asFloat())
        background_decorations.back().setPosition(element["left"].asFloat(), element["top"].asFloat());

    }

    std::vector<Entity> entities;
    for (auto const &element : root["entities"]) {


        Json::Value entity;   // will contain the root value after parsing.
        std::ifstream stream(element["file name"].asString(), std::ifstream::binary);
        stream >> entity;
        entities.emplace_back(Entity(*(textureManager_out += entity["texture name"].asString())));
        entities.back().SetHealth(entity["health"].asInt());
        entities.back().setPosition(element["spawn location"]["left"].asFloat(),element["spawn location"]["top"].asFloat() );



    }


    return entities;


}

std::string GameScene::Name() const {
    return _name;
}

decltype(GameScene::background_decorations)  const &GameScene::BackDecoration() const {
    return background_decorations;
}

decltype(GameScene::foreground_decorations) const &GameScene::FrontDecoration() {
    return foreground_decorations;
}

decltype(GameScene::geometry) const &GameScene::GetCollisionBoxes() {
    return geometry;
}

decltype(GameScene::parallaxes) const &GameScene::DoParallax(const sf::Vector2f &location) {
    for(auto & parallax : parallaxes){
        parallax.ApplyParallax(location);
    }
    return parallaxes;
}

GameScene::GameScene(const std::string &json_file, TextureManager &textureManager_out) {
    LoadFromJson(json_file, textureManager_out);
}

bool GameScene::isActive() {
    return true;
}


