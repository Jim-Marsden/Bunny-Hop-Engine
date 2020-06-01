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
    auto should_jump = Should_jump;


    _movement.EnableValue("jump", should_jump);
    _movement.ResetTimer("jump");


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

