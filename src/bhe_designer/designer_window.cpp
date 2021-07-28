//
// Created by james on 7/25/2021.
//

#include "designer_window.h"
#include <utility>
designer_window::designer_window(unsigned int x, unsigned int y, std::string  title_in = "Bunny Hop Designer") : x{x}, y{y}, title{std::move(title_in)} {

}
designer_window::exit_code designer_window::run() {
    sf::RenderWindow window(sf::VideoMode(x, y), title);
    tgui::Gui gui(window);

    if(!active_menu) {
        active_menu = tgui::MenuBar::create();
        active_menu->addMenu("File");
        active_menu->addMenuItem("Load");
        active_menu->addMenuItem("Save");
        active_menu->addMenuItem("Exit");

        active_menu->addMenu("Tools");
        active_menu->addMenuItem("Settings");
        active_menu->addMenuItem("About");
    }

    gui.add(active_menu);
    gui.mainLoop();


    return exit_code::normal;
}
