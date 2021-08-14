//
// Created by Jim Marsden on 7/25/2021.
//

#ifndef BUNNY_HOP_CORE_DESIGNERWINDOW_H
#define BUNNY_HOP_CORE_DESIGNERWINDOW_H

#include "gui_modes.hpp"

#include <TGUI/TGUI.hpp>
#include <string>


class designerWindow {
protected:
    tgui::MenuBar::Ptr activeMenu;
    sf::RenderWindow & window;
    tgui::Gui & gui;
    std::vector<bhe::designer::gui_modes> modes;


public:
    enum struct exitCode {
        Normal = 0,
        NullFunction,
        FunctionFailed,
    };

    designerWindow() = delete;
//    designerWindow(unsigned int x, unsigned int y, std::string title);
    designerWindow(sf::RenderWindow  &windowIn, tgui::Gui & gui);
    designerWindow(designerWindow const &) = delete;
    designerWindow(designerWindow &&) = delete;

    designerWindow &operator=(designerWindow const &) = delete;

    ~designerWindow() = default;

    void addMode(bhe::designer::gui_modes const & guiModes);

    exitCode run();
};


#endif//BUNNY_HOP_CORE_DESIGNERWINDOW_H
