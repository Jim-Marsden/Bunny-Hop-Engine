//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_GAMESCENE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_GAMESCENE_HPP

#include <bhe_core/textureManager.hpp>
#include <bhe_core/parallax.hpp>
#include <bhe_core/drawable.hpp>
#include <bhe_core/entity.hpp>

#include <string>
#include <vector>

namespace bhe {
    class gameScene {
        std::string name_;

        //TODO parallax class
        std::vector<parallax> parallaxes_;
        std::vector<sf::RectangleShape> geometry_;
        std::vector<bhe::drawable> background_decorations_;
        std::vector<bhe::drawable> foreground_decorations_;


    public:
        gameScene() = default;

        ~gameScene() = default;

        gameScene(gameScene const &) = default;

        gameScene(gameScene &&) = default;

        gameScene &operator=(gameScene &&) = default;

        gameScene &operator=(gameScene const &) = default;

        gameScene(std::string const &Json_File, textureManager &Texture_Manager_Out);

        [[nodiscard]]decltype(parallaxes_) const &DoParallax(sf::Vector2f const &Location);

        [[nodiscard]] decltype(geometry_) const &GetCollisionBoxes();

        [[nodiscard]]decltype(foreground_decorations_) const &FrontDecoration();

        [[nodiscard]]decltype(background_decorations_) const &BackDecoration() const;

        [[nodiscard]] std::string Name() const;

        std::vector<entity> LoadFromJson(std::string const &Json_File, textureManager &Texture_Manager_Out);

        bool IsActive();
    };


} //namespace bhe

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_GAMESCENE_HPP
