//
// Created by snizzfox on 5/16/20.
//

#include <iostream>
#include <json/json.h>
#include <fstream>
#include "player.hpp"

bhe::player::player(const sf::Sprite &Sprite) : bhe::entity(Sprite) {

}

bhe::player::player(const sf::Texture &Texture) : entity(Texture) {


}

void bhe::player::DoJump(const bool &Should_Jump) {
    auto should_jump = Should_Jump;


    movement_.EnableValue("jump", should_jump);
    movement_.ResetTimer("jump");


}

void bhe::player::MoveRight(bool const &Should_Jump) {
    movement_.EnableValue("move right", Should_Jump);

}

void bhe::player::MoveDown(bool const &Should_Jump) {
    movement_.EnableValue("move down", Should_Jump);


}

void bhe::player::MoveLeft(bool const &Should_Jump) {
    movement_.EnableValue("move left", Should_Jump);


}

sf::Vector2f bhe::player::GetPos() const {
    return sprite_.getPosition();
}

