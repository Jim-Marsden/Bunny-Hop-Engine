//
// Created by Jim Marsden on 7/25/2021.
//

#include "designerWindow.h"
#include "gui_helpers.hpp"
designerWindow::exitCode designerWindow::run()
{
	gui.add(activeMenu);

	return exitCode::Normal;
}
void designerWindow::add_mode(bhe::designer::gui_modes const& gui_modes)
{
	modes.push_back(gui_modes);
	activeMenu->addMenu("Modes");
	activeMenu->addMenuItem(gui_modes.mode_name);
	activeMenu->connectMenuItem("Modes", gui_modes.mode_name, [&gui_modes, this]() {
		for (auto const& modes_element : this->modes) {
			for (auto const& element : modes_element.to_draw) gui.remove(element);
		}
		for (auto const& e : gui_modes.to_draw) gui.add(e);
	});
}
designerWindow::designerWindow(sf::RenderWindow& window_in, tgui::Gui& gui_in)
		:window{window_in}, gui{gui_in}, activeMenu{tgui::MenuBar::create()}
{
	activeMenu = bhe::designer::default_menubar(window, gui);
}
