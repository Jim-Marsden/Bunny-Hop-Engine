//
// Created by Jim Marsden on 5/16/20.
//

#include <iostream>
#include <json/json.h>
#include <fstream>
#include "player.hpp"

bhe::player::player(const sf::Sprite &sprite) :bhe::Entity(sprite) {

}

bhe::player::player(const sf::Texture &texture) :Entity(texture) {


}

void bhe::player::do_jump(const bool &should_jump) {
//    auto should_jump = should_jump;

	movement_.enable_value("jump", should_jump);
	movement_.reset_timer("jump");


}

void bhe::player::move_right(bool const &should_jump) {
	movement_.enable_value("move right", should_jump);

}

void bhe::player::move_down(bool const &should_jump) {
	movement_.enable_value("move down", should_jump);


}

void bhe::player::move_left(bool const &should_jump) {
	movement_.enable_value("move left", should_jump);


}

sf::Vector2f bhe::player::get_pos() const {
    return sprite.getPosition();
}

