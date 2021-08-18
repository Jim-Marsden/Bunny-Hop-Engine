//
// Created by Jim Marsden on 6/6/20.
//
#include "DesignerWindow.h"
#include "scene_designer.hpp"

//Do I really want to keep this style of ugly gui interface? All the objects, etc.?
/* TODO:
 * 1) Implement Modes
 * 2) Implement A status bar
 */


int main()
{

	sf::RenderWindow sf_window{sf::VideoMode{500, 500}, "Hello!"};
	tgui::Gui gui{sf_window};
//
	DesignerWindow window(sf_window, gui);

	bhe::designer::gui_modes mode_1{.mode_name{L"!designer \U0001f98a!"}, .panel{tgui::Panel::create()}};
	auto mode_2{bhe::designer::create_scene_designer()};

	auto l = tgui::Label::create("stuff, stuff, stuff, more stuff!");
	l->setAutoSize(true);
	l->setPosition(0, 40);
	mode_1.panel->add(l);

//    window.add_mode(bhe::designer::create_scene_designer());

	window.add_mode(mode_1);
	window.add_mode(mode_2);
	window.run();

	return {};
}