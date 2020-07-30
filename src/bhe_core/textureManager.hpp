//
// Created by james on 5/15/2020.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_TEXTUREMANAGER_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_TEXTUREMANAGER_HPP
#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <memory>


namespace bhe {
    class textureManager {
        std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
        //std::vector<std::shared_ptr<sf::Texture>> textures_;
    public:
        textureManager() = default;

        ~textureManager() = default;

        textureManager(textureManager &&) = delete;

        textureManager(textureManager const &) = delete;

        textureManager &operator=(textureManager const &) = delete;

        textureManager &operator=(textureManager &&) = delete;


        size_t AddTexture(std::string const &Texture_Name);

        void Clear();

        [[nodiscard]] std::shared_ptr<sf::Texture> MakeTexture(std::string const &String);

        [[nodiscard]] std::shared_ptr<sf::Texture> CGetTexture(std::string const &String) const;


        [[nodiscard]] bool CheckTexture(std::string const &Texture_Name) const;

        std::shared_ptr<sf::Texture> operator+=(std::string const &Texture_Name);

        std::shared_ptr<sf::Texture> operator=(std::string const &Texture_Name);


    };
} //namespace bhe


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_TEXTUREMANAGER_HPP
