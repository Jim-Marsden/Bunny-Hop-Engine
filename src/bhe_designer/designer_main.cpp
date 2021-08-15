//
// Created by Jim Marsden on 6/6/20.
//
#include "designerWindow.h"
#include "gui_modes.hpp"
#include <bhe_designer/windowManager.hpp>
#include <iostream>

//Do I really want to keep this style of ugly gui interface? All the objects, etc?
/* TODO:
 * 1) Implement Modes
 * 2) Implement A status bar
 */


int main(){
    bhe::designer::gui_modes m1{.mode_name{L"!designer \U0001f98a!"}};
    sf::RenderWindow sfWindow{sf::VideoMode{500, 500}, "Hello!"};
    tgui::Gui gui{sfWindow};
//
    designerWindow window(sfWindow, gui);

    auto l = tgui::Label::create("stuff, stuff, stuff, more stuff!");
    l->setAutoSize(true);
    l->setPosition(0, 40);
    m1.to_draw.emplace_back(l);

    window.addMode(m1);
    window.run();

    return {};
}