//
// Created by snizzfox on 7/3/20.
//

#include "windowManager.hpp"
#include <iostream>
#include <string>

auto windowManager::Run() -> bhe::returnStatus<void> {
    if (!_has_iniliziazed)InitilalizeElements();

    window.create(sf::VideoMode(800, 800), "I'm the designer!");

    while (window.isOpen()) {
        event.DoEvents();
        window.clear(sf::Color(0xa, 0xa, 0xa));
        window.display();

    }

    return {true, bhe::returnStatusCode::Normal};
}

windowManager::~windowManager() {
    for (auto &element : elements) {
        element.Close();
    }

}

auto windowManager::InitilalizeElements() -> bhe::returnStatus<int> {
    if (_has_iniliziazed) return {0, false, bhe::returnStatusCode::SingleRunFunctionReran};
    int result{};
    _has_iniliziazed = true;

    for (auto &element : elements) {

        if (auto[status, message] = element.InitWindow(); status) {
            result++;
        } else {
            std::cerr << "Error failed to initialize with message: " << static_cast<int>( message);
        }

    }

    return {result, true, bhe::returnStatusCode::Normal};
}

