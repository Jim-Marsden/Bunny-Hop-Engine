//
// Created by james on 7/25/2021.
//

#include "designerWindow.h"
#include "gui_helpers.hpp"
#include <iostream>
#include <utility>
designerWindow::designerWindow(unsigned int x, unsigned int y, std::string title_in = "Bunny Hop Designer") : window{sf::VideoMode{x, y}, title_in} {
}
designerWindow::exitCode designerWindow::run() {
    //    sf::RenderWindow window(sf::VideoMode(x, y), title);
    tgui::Gui gui(window);

    if (!activeMenu) {
        activeMenu = bhe::designer::default_menubar(window, gui);
    }

    gui.add(activeMenu);
//    gui.add(bhe::designer::about_dialog());
    gui.mainLoop();


    return exitCode::Normal;
}
