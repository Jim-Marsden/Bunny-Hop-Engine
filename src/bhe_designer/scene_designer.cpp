//
// Created by Jim Marsden on 8/15/2021.
//

#include "scene_designer.hpp"
#include <iostream>
bhe::designer::gui_modes bhe::designer::create_scene_designer()
{
	bhe::designer::gui_modes rv;
	rv.mode_name = L"Designer";

	rv.panel = tgui::Panel::create();
	auto geometry_button{tgui::Button::create("Geometry!")};

	rv.panel->add(geometry_button, "Geometry_Button");

	auto canvas = tgui::Canvas::create();
	canvas->setSize("100%", "100% - 30");
	canvas->setPosition(0, 30);
	rv.panel->add(canvas);

	geometry_button->onClick(
			[](){}
	);

	return rv;
}
