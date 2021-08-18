//
// Created by Jim Marsden on 8/6/2021.
//

#ifndef BUNNY_HOP_CORE_GUI_MODES_HPP
#define BUNNY_HOP_CORE_GUI_MODES_HPP
#include <vector>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <string>

namespace bhe::designer {
struct gui_modes {
	using EventCallback = std::function<void()>;
	std::wstring mode_name;
	tgui::Panel::Ptr panel;
};
}// namespace bhe::designer

#endif//BUNNY_HOP_CORE_GUI_MODES_HPP
