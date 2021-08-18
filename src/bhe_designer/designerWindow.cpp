//
// Created by Jim Marsden on 7/25/2021.
//

#include "DesignerWindow.h"
#include "gui_helpers.hpp"
DesignerWindow::exitCode DesignerWindow::run()
{
	gui.add(activeMenu);

	return exitCode::Normal;
}
void DesignerWindow::add_mode(bhe::designer::gui_modes const& gui_modes)
{
	modes.push_back(gui_modes);
	activeMenu->addMenuItem(gui_modes.mode_name);
	activeMenu->connectMenuItem("Modes", gui_modes.mode_name, [&gui_modes, this]() {
		for(auto const& current_mode : this->modes) gui.remove(current_mode.panel);
		gui.add(gui_modes.panel);
	});
}
DesignerWindow::DesignerWindow(sf::RenderWindow& window_in, tgui::Gui& gui_in)
		:window{window_in}, gui{gui_in}, activeMenu{tgui::MenuBar::create()}
{
	activeMenu = bhe::designer::default_menubar(window, gui);
}
