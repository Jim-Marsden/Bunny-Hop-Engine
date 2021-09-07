//
// Created by snizzfox on 5/30/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_JSON_PARSER_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_JSON_PARSER_HPP

#include <json/value.h>
#include <bhe_core/parallax.hpp>
#include <bhe_core/textureManager.hpp>
#include <bhe_core/drawable.hpp>
#include <bhe_core/entity.hpp>
#include <bhe_core/player.hpp>


namespace bhe::json_parsers {

    [[nodiscard]] auto load(const std::string &json_file) -> Json::Value;

    [[nodiscard]] auto parse_parallax(Json::Value const &root,
                                     bhe::textureManager &texture_manager) -> std::vector<bhe::Parallax>;

    [[nodiscard]] auto parse_geometry(Json::Value const &root) -> std::vector<sf::RectangleShape>;


    [[nodiscard]] auto
    parse_decorations(Json::Value const &root, bhe::textureManager &texture_manager) -> std::vector<bhe::Drawable>;

    [[nodiscard]] auto parse_entities(Json::Value const &Root,
                                     bhe::textureManager &texture_manager) -> std::vector<bhe::Entity>;

    [[deprecated]] [[nodiscard]] auto
    parse_entity(Json::Value const &root, bhe::textureManager &texture_manager) -> bhe::Entity;

    [[nodiscard]] auto
    load_entity(std::string const & file_name, bhe::textureManager &texture_manager) -> bhe::Entity;

    [[nodiscard]] auto
    parse_player(std::string_view const &file_name, bhe::textureManager &texture_manager) -> bhe::player;

}

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_JSON_PARSER_HPP
