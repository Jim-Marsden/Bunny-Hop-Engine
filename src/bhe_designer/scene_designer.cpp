//
// Created by Jim Marsden on 8/15/2021.
//

#include "scene_designer.hpp"
bhe::designer::gui_modes bhe::designer::create_scene_designer()
{
	bhe::designer::gui_modes rv;
	rv.mode_name = L"Designer";

	rv.panel = tgui::Panel::create();
	rv.panel->setPosition(0, 20);

	rv.panel->add(tgui::Label::create("Hello, you!"), "Label1");

	return rv;
}
