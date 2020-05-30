//
// Created by snizzfox on 5/16/20.
//

#include <iostream>
#include <json/json.h>
#include <fstream>
#include "player.hpp"

mt::player::player(const sf::Sprite &Sprite) : mt::entity(Sprite) {

}

mt::player::player(const sf::Texture &Texture) : entity(Texture) {


}

void mt::player::DoJump(const bool &Should_jump) {
    _movement.EnableValue("jump", Should_jump);


}

void mt::player::MoveRight(bool const &Should_jump) {
    _movement.EnableValue("move right", Should_jump);

}

void mt::player::MoveDown(bool const &Should_jump) {
    _movement.EnableValue("move down", Should_jump);


}

void mt::player::MoveLeft(bool const &Should_jump) {
    _movement.EnableValue("move left", Should_jump);


}

sf::Vector2f mt::player::GetPos() const {
    return _sprite.getPosition();
}

auto load_file_to_json(const std::string &Json_file) {
    Json::Value root; // will contain the root value after parsing.
    std::ifstream stream(Json_file, std::ifstream::binary);
    stream >> root;
    return root;
}

mt::player mt::load_player_from_file(std::string const &File_name, mt::textureManager &Texture_manager) {


    auto root = load_file_to_json(File_name);

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
        std::cout << "Movement " << movement_element["name"].asString() << '\t';

        std::cout << "X " << movement_element["speed x"].asFloat() << '\t';
        std::cout << "Y " << movement_element["speed y"].asFloat() << '\t';
        std::cout << "Y " << movement_element["enabled"].asBool() << '\n';

        result.AddMovement(movement_element["name"].asString(),
                           {movement_element["enabled"].asBool(), movement_element["speed x"].asFloat(),
                            movement_element["speed y"].asFloat()});

    }


    return result;
}
