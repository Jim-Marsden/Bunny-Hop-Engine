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


namespace bhe::json_parsers {

    [[nodiscard]] auto load(const std::string &Json_file) -> Json::Value;

    [[nodiscard]] auto parse_parallax(Json::Value const &Root,
                                      bhe::textureManager &Texture_manager) -> std::vector<bhe::parallax>;

    [[nodiscard]] auto parse_geometry(Json::Value const &Root) -> std::vector<sf::RectangleShape>;


    [[nodiscard]] auto
    parse_decorations(Json::Value const &Root, bhe::textureManager &Texture_manager) -> std::vector<bhe::drawable>;

    [[nodiscard]] auto parse_entities(Json::Value const &Root,
                                      bhe::textureManager &Texture_manager) -> std::vector<bhe::entity>;

    [[deprecated]] [[nodiscard]] auto
    parse_entity(Json::Value const &Root, bhe::textureManager &Texture_manager) -> bhe::entity;

    [[nodiscard]] auto
    load_entity(std::string const & File_Name, bhe::textureManager &Texture_manager) -> bhe::entity;

    [[nodiscard]] auto
    parse_player(std::string_view const &Root, bhe::textureManager &Texture_manager) -> bhe::player;

}

#endif //MOONLIGHT_TRAILS_JSON_PARSER_HPP
