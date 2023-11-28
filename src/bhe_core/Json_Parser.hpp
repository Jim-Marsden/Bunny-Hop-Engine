//
// Created by snizzfox on 5/30/20.
//

#pragma once
#include <nlohmann/json.hpp>
#include "bhe_core/parallax.hpp"
#include "bhe_core/textureManager.hpp"
#include "bhe_core/drawable.hpp"
#include "bhe_core/entity.hpp"
#include "bhe_core/player.hpp"


namespace bhe::json_parsers {
    using json_t = nlohmann::json;

    [[nodiscard]] auto load(const std::string &json_file) -> nlohmann::json;//Json::Value;

    [[nodiscard]] auto parse_parallax(json_t const &root,
                                     bhe::textureManager &texture_manager) -> std::vector<bhe::Parallax>;

    [[nodiscard]] auto parse_geometry(json_t const &root) -> std::vector<sf::RectangleShape>;


    [[nodiscard]] auto
    parse_decorations(json_t const &root, bhe::textureManager &texture_manager) -> std::vector<bhe::Drawable>;

    [[nodiscard]] auto parse_entities(json_t const &Root,
                                     bhe::textureManager &texture_manager) -> std::vector<bhe::Entity>;

    [[deprecated]] [[nodiscard]] auto
    parse_entity(json_t const &root, bhe::textureManager &texture_manager) -> bhe::Entity;

    [[nodiscard]] auto
    load_entity(std::string const & file_name, bhe::textureManager &texture_manager) -> bhe::Entity;

    [[nodiscard]] auto
    parse_player(std::string_view const &file_name, bhe::textureManager &texture_manager) -> bhe::player;

}
