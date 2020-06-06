//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
#define MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <memory>


namespace bhe {
    class textureManager {
        std::map<std::string, std::shared_ptr<sf::Texture>> textures;
        //std::vector<std::shared_ptr<sf::Texture>> textures;
    public:
        textureManager() = default;

        ~textureManager() = default;

        size_t AddTexture(std::string const &Texture_name);

        void Clear();

        [[nodiscard]] std::shared_ptr<sf::Texture> MakeTexture(std::string const &String);

        [[nodiscard]] std::shared_ptr<sf::Texture> CGetTexture(std::string const &String) const;


        [[nodiscard]] bool CheckTexture(std::string const &Texture_name) const;

        std::shared_ptr<sf::Texture> operator+=(std::string const &Texture_name);

        std::shared_ptr<sf::Texture> operator=(std::string const &Texture_name);


    };
} //namespace bhe


#endif //MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
