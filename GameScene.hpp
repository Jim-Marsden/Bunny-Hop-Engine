//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_GAMESCENE_HPP
#define MOONLIGHT_TRAILS_GAMESCENE_HPP

#include "TextureManager.hpp"
#include "Parallax.hpp"
#include "Drawable.hpp"
#include "Entity.hpp"

#include <string>
#include <vector>

namespace MT {
    class GameScene {
        std::string _name;

        //TODO Parallax class
        std::vector<Parallax> parallaxes;
        std::vector<sf::RectangleShape> geometry;
        std::vector<MT::Drawable> background_decorations;
        std::vector<MT::Drawable> foreground_decorations;


    public:
        GameScene() = default;
        GameScene(std::string const &json_file, TextureManager &textureManager_out);

        [[nodiscard]]decltype(parallaxes) const &  DoParallax(sf::Vector2f const &location);

        [[nodiscard]] decltype(geometry) const &  GetCollisionBoxes();

        [[nodiscard]]decltype(foreground_decorations) const &  FrontDecoration();

        [[nodiscard]]decltype(background_decorations) const & BackDecoration() const;

        [[nodiscard]] std::string Name() const;

        std::vector<Entity> LoadFromJson(std::string const &json_file, TextureManager &textureManager_out);

        bool isActive();
    };


} //namespace MT

#endif //MOONLIGHT_TRAILS_GAMESCENE_HPP
