//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_GAMESCENE_HPP
#define MOONLIGHT_TRAILS_GAMESCENE_HPP

#include "textureManager.hpp"
#include "parallax.hpp"
#include "drawable.hpp"
#include "entity.hpp"

#include <string>
#include <vector>

namespace mt {
    class gameScene {
        std::string name;

        //TODO parallax class
        std::vector<parallax> parallaxes;
        std::vector<sf::RectangleShape> geometry;
        std::vector<mt::drawable> background_decorations;
        std::vector<mt::drawable> foreground_decorations;


    public:
        gameScene() = default;

        gameScene(std::string const &Json_file, textureManager &Texture_manager_out);

        [[nodiscard]]decltype(parallaxes) const &DoParallax(sf::Vector2f const &Location);

        [[nodiscard]] decltype(geometry) const &GetCollisionBoxes();

        [[nodiscard]]decltype(foreground_decorations) const &FrontDecoration();

        [[nodiscard]]decltype(background_decorations) const &BackDecoration() const;

        [[nodiscard]] std::string Name() const;

        std::vector<entity> LoadFromJson(std::string const &Json_file, textureManager &Texture_manager_out);

        bool IsActive();
    };


} //namespace mt

#endif //MOONLIGHT_TRAILS_GAMESCENE_HPP
