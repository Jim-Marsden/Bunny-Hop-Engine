//
// Created by Jim Marsden on 7/25/2021.
//

#include "DesignerWindow.h"
#include "gui_helpers.hpp"
DesignerWindow::exitCode DesignerWindow::run()
{
	gui.add(activeMenu);

	sf::Event event{};
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		gui.draw();
		active_mode->panel->get("canvas").clear();
		window.display();
	}

	return exitCode::Normal;
}
void DesignerWindow::add_mode(bhe::designer::gui_modes const& gui_modes)
{
	modes.push_back(gui_modes);
	activeMenu->addMenuItem(gui_modes.mode_name);
	activeMenu->connectMenuItem("Modes", gui_modes.mode_name, [&gui_modes, this]() {
		for(auto const& current_mode : this->modes) gui.remove(current_mode.panel);
		gui_modes.panel->setSize("100%", "100% - 20");
		gui_modes.panel->setPosition(0, 20);
		gui.add(gui_modes.panel);
		active_mode = &gui_modes;
	});
}
DesignerWindow::DesignerWindow(sf::RenderWindow& window_in, tgui::Gui& gui_in)
		:window{window_in}, gui{gui_in}, activeMenu{tgui::MenuBar::create()}, active_mode{nullptr}
{
	activeMenu = bhe::designer::default_menubar(window, gui);
}
