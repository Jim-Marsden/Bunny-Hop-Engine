//
// Created by snizzfox on 7/3/20.
//

#include "windowManager.hpp"
#include <iostream>
#include <string>

auto windowManager::Run() -> bhe::returnStatus<void> {
    if (!_has_iniliziazed)InitilalizeElements();

    return {true, "Hello"};
}

windowManager::~windowManager() {
    for (auto &element : elements) {
        element.Close();
    }

}

auto windowManager::InitilalizeElements() -> bhe::returnStatus<int> {
    int result{};
    _has_iniliziazed = true;

    for (auto &element : elements) {

        if (auto[status, message] = element.InitWindow(); status) {
            result++;
        } else {
            std::cerr << "Error failed to initialize with message: " << message;
        }

    }

    return {result, false, "Not implemented"};
}

