//
// Created by james on 5/15/2020.
//

#include "textureManager.hpp"

size_t bhe::textureManager::AddTexture(const std::string &Texture_Name) {
    if (textures_[Texture_Name] == nullptr) {
      textures_[Texture_Name] = std::make_shared<sf::Texture>();
        if (!textures_[Texture_Name]->loadFromFile(Texture_Name)) {
          textures_[Texture_Name] = nullptr;
            textures_.erase(Texture_Name);
        }
    }
    return textures_.size();
}

void bhe::textureManager::Clear() {
    textures_.clear();

}

std::shared_ptr<sf::Texture>
bhe::textureManager::MakeTexture(const std::string &String) {
    AddTexture(String);
    return textures_[String];
}

std::shared_ptr<sf::Texture>
bhe::textureManager::CGetTexture(const std::string &String) const {
    if (textures_.at(String) != nullptr) return textures_.at(String);
    return nullptr;

}

bool bhe::textureManager::CheckTexture(const std::string &Texture_Name) const {
    return textures_.at(Texture_Name) != nullptr;
}

std::shared_ptr<sf::Texture>
bhe::textureManager::operator+=(const std::string &Texture_Name) {
    return MakeTexture(Texture_Name);
}

std::shared_ptr<sf::Texture>
bhe::textureManager::operator=(const std::string &Texture_Name) {
    Clear();
    return MakeTexture(Texture_Name);
}

