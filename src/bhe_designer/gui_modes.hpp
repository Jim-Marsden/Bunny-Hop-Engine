//
// Created by james on 8/6/2021.
//

#ifndef BUNNY_HOP_CORE_GUI_MODES_HPP
#define BUNNY_HOP_CORE_GUI_MODES_HPP
#include <vector>
#include <TGUI/TGUI.hpp>
#include <functional>
#include <string>

namespace bhe::designer {
    struct gui_modes {
        std::wstring mode_name;
        using event_callback = std::function<void()>;
        std::vector<tgui::Widget::Ptr> to_draw;
        event_callback resize;
    };
}// namespace bhe::designer

#endif//BUNNY_HOP_CORE_GUI_MODES_HPP
