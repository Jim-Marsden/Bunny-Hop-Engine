//
// Created by Jim Marsden on 7/25/2021.
//

#ifndef BUNNY_HOP_CORE_DESIGNERWINDOW_H
#define BUNNY_HOP_CORE_DESIGNERWINDOW_H

#include "gui_modes.hpp"

#include <TGUI/TGUI.hpp>
#include <string>

class DesignerWindow {
protected:
	tgui::MenuBar::Ptr active_menu;
	sf::RenderWindow& window;
	tgui::Gui& gui;
	std::vector<bhe::designer::gui_modes> modes;

public:
	enum struct ExitCode {
		Normal = 0,
		NullFunction,
		FunctionFailed,
	};

	DesignerWindow() = delete;
//    designerWindow(unsigned int x, unsigned int y, std::string title);
	DesignerWindow(sf::RenderWindow& window_in, tgui::Gui& gui);
	DesignerWindow(DesignerWindow const&) = delete;
	DesignerWindow(DesignerWindow&&) = delete;

	DesignerWindow& operator=(DesignerWindow const&) = delete;

	~DesignerWindow() = default;

	void add_mode(bhe::designer::gui_modes const& gui_modes);

	ExitCode run();
};

#endif//BUNNY_HOP_CORE_DESIGNERWINDOW_H
