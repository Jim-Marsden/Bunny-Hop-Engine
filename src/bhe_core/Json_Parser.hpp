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

    [[nodiscard]] auto Load(const std::string &Json_File) -> Json::Value;

    [[nodiscard]] auto ParseParallax(Json::Value const &Root,
                                     bhe::textureManager &Texture_Manager) -> std::vector<bhe::parallax>;

    [[nodiscard]] auto ParseGeometry(Json::Value const &Root) -> std::vector<sf::RectangleShape>;


    [[nodiscard]] auto
    ParseDecorations(Json::Value const &Root, bhe::textureManager &Texture_Manager) -> std::vector<bhe::drawable>;

    [[nodiscard]] auto ParseEntities(Json::Value const &Root,
                                     bhe::textureManager &Texture_Manager) -> std::vector<bhe::entity>;

    [[deprecated]] [[nodiscard]] auto
    ParseEntity(Json::Value const &Root, bhe::textureManager &Texture_Manager) -> bhe::entity;

    [[nodiscard]] auto
    LoadEntity(std::string const & File_Name, bhe::textureManager &Texture_Manager) -> bhe::entity;

    [[nodiscard]] auto
    ParsePlayer(std::string_view const &File_Name, bhe::textureManager &Texture_Manager) -> bhe::player;

}

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_JSON_PARSER_HPP
