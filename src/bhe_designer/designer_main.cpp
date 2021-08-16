//
// Created by Jim Marsden on 6/6/20.
//
#include "designerWindow.h"
#include "scene_designer.hpp"
#include "gui_modes.hpp"
#include <iostream>

//Do I really want to keep this style of ugly gui interface? All the objects, etc?
/* TODO:
 * 1) Implement Modes
 * 2) Implement A status bar
 */


int main(){
    sf::RenderWindow sfWindow{sf::VideoMode{500, 500}, "Hello!"};
    tgui::Gui gui{sfWindow};
//
    designerWindow window(sfWindow, gui);

    bhe::designer::gui_modes m1{.mode_name{L"!designer \U0001f98a!"}};
	auto m2{bhe::designer::create_scene_designer()};

	auto l = tgui::Label::create("stuff, stuff, stuff, more stuff!");
	l->setAutoSize(true);
	l->setPosition(0, 40);
	m1.to_draw.emplace_back(l);

//    window.addMode(bhe::designer::create_scene_designer());

window.addMode(m1);
window.addMode(m2);
    window.run();

    return {};
}