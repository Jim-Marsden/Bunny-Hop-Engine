//
// Created by james on 7/25/2021.
//

#include "designer_window.h"
#include "gui_helpers.hpp"
#include <iostream>
#include <utility>
designer_window::designer_window(unsigned int x, unsigned int y, std::string title_in = "Bunny Hop Designer") : window{sf::VideoMode{x, y}, title_in} {
}
designer_window::exit_code designer_window::run() {
    //    sf::RenderWindow window(sf::VideoMode(x, y), title);
    tgui::Gui gui(window);

    if (!active_menu) {
        active_menu = bhe::designer::default_menubar(window, gui);
    }

    gui.add(active_menu);
//    gui.add(bhe::designer::about_dialog());
    gui.mainLoop();


    return exit_code::normal;
}
