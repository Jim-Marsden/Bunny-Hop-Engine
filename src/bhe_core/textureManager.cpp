//
// Created by james on 5/15/2020.
//

#include "textureManager.hpp"

size_t bhe::textureManager::AddTexture(const std::string &Texture_name) {
    if (textures[Texture_name] == nullptr) {
        textures[Texture_name] = std::make_shared<sf::Texture>();
        if (!textures[Texture_name]->loadFromFile(Texture_name)) {
            textures[Texture_name] = nullptr;
            textures.erase(Texture_name);
        }
    }
    return textures.size();
}

void bhe::textureManager::Clear() {
    textures.clear();

}

std::shared_ptr<sf::Texture>
bhe::textureManager::MakeTexture(const std::string &String) {
    AddTexture(String);
    return textures[String];
}

std::shared_ptr<sf::Texture>
bhe::textureManager::CGetTexture(const std::string &String) const {
    if (textures.at(String) != nullptr) return textures.at(String);
    return nullptr;

}

bool bhe::textureManager::CheckTexture(const std::string &Texture_name) const {
    return textures.at(Texture_name) != nullptr;
}

std::shared_ptr<sf::Texture>
bhe::textureManager::operator+=(const std::string &Texture_name) {
    return MakeTexture(Texture_name);
}

std::shared_ptr<sf::Texture>
bhe::textureManager::operator=(const std::string &Texture_name) {
    Clear();
    return MakeTexture(Texture_name);
}

