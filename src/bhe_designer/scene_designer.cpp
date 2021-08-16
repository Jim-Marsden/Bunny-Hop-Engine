//
// Created by Jim Marsden on 8/15/2021.
//

#include "scene_designer.hpp"
bhe::designer::gui_modes bhe::designer::create_scene_designer()
{
	bhe::designer::gui_modes rv;
	rv.mode_name = L"Designer";

	auto main_panel = tgui::Panel::create();
	main_panel->setPosition(0, 20);

	main_panel->add(tgui::Label::create("Hello, you!"), "Label1");

	rv.to_draw.push_back(main_panel);
	return rv;
}
