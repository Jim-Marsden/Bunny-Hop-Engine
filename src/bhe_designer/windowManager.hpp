//
// Created by snizzfox on 7/3/20.
//

#ifndef BUNNY_HOP_CORE_WINDOWMANAGER_HPP
#define BUNNY_HOP_CORE_WINDOWMANAGER_HPP

#include <bhe_core/Return_Status.hpp>
#include <bhe_designer/baseWindowElement.hpp>
#include <bhe_core/systemEvent.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class windowManager {
protected:
    tgui::Gui gui;
    sf::RenderWindow window;
    std::vector<baseWindowElement> elements;

    bhe::systemEvent event{window};


    bool _has_iniliziazed;
public:
    windowManager() = default;

    ~windowManager();

    windowManager(windowManager const &) = delete;

    windowManager(windowManager &&) = delete;


    auto Run() -> bhe::returnStatus<void>;

    auto InitilalizeElements() -> bhe::returnStatus<int>; // Number of elements initialzed;



};


#endif //BUNNY_HOP_CORE_WINDOWMANAGER_HPP
