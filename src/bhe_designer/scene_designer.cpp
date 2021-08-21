//
// Created by Jim Marsden on 8/15/2021.
//

#include "scene_designer.hpp"
#include <iostream>
sf::RectangleShape rectangle_shape{};

bhe::designer::gui_modes bhe::designer::create_scene_designer()
{
	bhe::designer::gui_modes rv;
	rv.mode_name = L"Designer";

	rv.panel = tgui::Panel::create();
	rv.panel->setWidgetName("main panel");
	auto geometry_button{tgui::Button::create("Geometry!")};

	rv.panel->add(geometry_button, "Geometry_Button");

	auto canvas = tgui::Canvas::create();
	canvas->setWidgetName("canvas");
	canvas->setSize("100%", "100% - 30");
	canvas->setPosition(0, 30);
	rectangle_shape.setSize({34, 34});



	rv.panel->add(canvas);
	canvas->clear(sf::Color::Magenta);

	canvas->display();
	std::cout <<  ((canvas) ?  "not null\n" : "null\n");
	geometry_button->onClick(
			[&rv, &canvas](){
				std::cout <<  ((canvas) ?  "not null\n" : "null\n");

				if(canvas) {
//					canvas->clear();
//					canvas->draw(rectangle_shape);
//					canvas->display();
					std::cout << "canvas is null?";
				}
				else{
					std::cout << "asdfasdf" << '\n';
				}
//				auto c = rv.panel->get<tgui::Canvas>("Canvas");
			}
	);

	return rv;
}
