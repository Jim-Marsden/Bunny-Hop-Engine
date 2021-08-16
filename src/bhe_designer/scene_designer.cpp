//
// Created by james on 8/15/2021.
//

#include "scene_designer.hpp"
bhe::designer::gui_modes bhe::designer::create_scene_designer()
{
	bhe::designer::gui_modes rv;

	auto temp_label = tgui::Label::create();
	temp_label->setWidgetName("temp_label");
	auto temp_grid = tgui::Group::create();
	auto x = tgui::Panel::create();
	x->setPosition(0, 20);


	temp_grid->add(tgui::Label::create("test"), "Label1");
//	temp_grid.get

	temp_grid->add(tgui::Label::create("test2"), "Label2");
	temp_grid->add(tgui::Label::create("test3"), "Label3");

	x->add(tgui::Label::create("Hello, you!"), "Label1");

	rv.mode_name = L"Designer";
//	rv.to_draw.push_back(temp_grid);
	rv.to_draw.push_back(x);
	return rv;

}
