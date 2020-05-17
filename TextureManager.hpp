//
// Created by james on 5/15/2020.
//

#ifndef MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
#define MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
inline namespace MT {
    class TextureManager {
        std::map<std::string, std::shared_ptr<sf::Texture>> textures;
        //std::vector<std::shared_ptr<sf::Texture>> textures;
    public:
        TextureManager() = default;
        ~TextureManager() = default;
        size_t AddTexture(std::string const & texture_name);
        void Clear();

        [[nodiscard]] std::shared_ptr<sf::Texture> MakeTexture(std::string const & string);
        [[nodiscard]] std::shared_ptr<sf::Texture> CGetTexture(std::string const & string) const;


        [[nodiscard]] bool CheckTexture(std::string const & texture_name) const;

        std::shared_ptr<sf::Texture> operator+=(std::string const & texture_name);
        std::shared_ptr<sf::Texture>  operator=(std::string const & texture_name);



    };
} //namespace MT


#endif //MOONLIGHT_TRAILS_TEXTUREMANAGER_HPP
