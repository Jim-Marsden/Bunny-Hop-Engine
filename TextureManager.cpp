//
// Created by james on 5/15/2020.
//

#include "TextureManager.hpp"

size_t MT::TextureManager::AddTexture(const std::string &texture_name) {
    if(textures[texture_name] == nullptr){
        textures[texture_name] = std::make_shared<sf::Texture>();
        if(!textures[texture_name]->loadFromFile(texture_name)){
            textures[texture_name] = nullptr;
            textures.erase(texture_name);
        }
    }
    return textures.size();
}

void MT::TextureManager::Clear() {
    textures.clear();

}

std::shared_ptr<sf::Texture> MT::TextureManager::MakeTexture(const std::string &string) {
    AddTexture(string);
    return textures[string];
}

std::shared_ptr<sf::Texture> MT::TextureManager::CGetTexture(const std::string &string) const {
    if(textures.at(string) != nullptr) return textures.at(string);
    return nullptr;

}

bool MT::TextureManager::CheckTexture(const std::string &texture_name) const {
    return textures.at(texture_name) != nullptr;
}

std::shared_ptr<sf::Texture> MT::TextureManager::operator+=(const std::string &texture_name) {
    return MakeTexture(texture_name);
}

std::shared_ptr<sf::Texture> MT::TextureManager::operator=(const std::string &texture_name) {
    Clear();
     return MakeTexture(texture_name);
}

