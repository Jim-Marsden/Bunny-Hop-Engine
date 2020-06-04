//
// Created by snizzfox on 5/30/20.
//

#ifndef MOONLIGHT_TRAILS_JSON_PARSER_HPP
#define MOONLIGHT_TRAILS_JSON_PARSER_HPP

#include <json/value.h>
#include "parallax.hpp"
#include "textureManager.hpp"
#include "drawable.hpp"
#include "entity.hpp"
#include "player.hpp"


namespace mt::json_parsers {

    [[nodiscard]] auto load(const std::string &Json_file) -> Json::Value;

    [[nodiscard]] auto parse_parallax(Json::Value const &Root,
                                      mt::textureManager &Texture_manager) -> std::vector<mt::parallax>;

    [[nodiscard]] auto parse_geometry(Json::Value const &Root) -> std::vector<sf::RectangleShape>;


    [[nodiscard]] auto
    load_decorations(Json::Value const &Root, mt::textureManager &Texture_manager) -> std::vector<mt::drawable>;

    [[nodiscard]] auto parse_entities(Json::Value const &Root,
                                      mt::textureManager &Texture_manager) -> std::vector<mt::entity>;

    [[nodiscard]] auto
    parse_entity(Json::Value const &Root, mt::textureManager &Texture_manager) -> mt::entity;

    [[nodiscard]] auto
    parse_player(std::string_view const &Root, mt::textureManager &Texture_manager) -> mt::player;

}

#endif //MOONLIGHT_TRAILS_JSON_PARSER_HPP
