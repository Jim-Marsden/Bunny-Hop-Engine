//
// Created by james on 7/25/2021.
//

#include "designerWindow.h"
#include "gui_helpers.hpp"
#include <iostream>
#include <utility>
designerWindow::exitCode designerWindow::run() {
    gui.add(activeMenu);
//    gui.add(bhe::designer::about_dialog());
    gui.mainLoop();

    return exitCode::Normal;
}
void designerWindow::addMode(bhe::designer::gui_modes const & guiModes) {
    modes.push_back(guiModes);
    activeMenu->addMenu("Modes");
    activeMenu->addMenuItem(guiModes.mode_name);
    activeMenu->connectMenuItem("Modes", guiModes.mode_name, [&guiModes, this]() {
        for(auto const & modes : this->modes){
            for(auto const & element : modes.to_draw) gui.remove(element);
        }
        for(auto const & e : guiModes.to_draw) gui.add(e);
    });
}
designerWindow::designerWindow(sf::RenderWindow &windowIn, tgui::Gui &guiin) : window{windowIn}, gui{guiin}, activeMenu{tgui::MenuBar::create()} {
    activeMenu = bhe::designer::default_menubar(window, gui);
}
