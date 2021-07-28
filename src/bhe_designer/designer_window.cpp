//
// Created by james on 7/25/2021.
//

#include "designer_window.h"
#include <iostream>
#include <utility>
designer_window::designer_window(unsigned int x, unsigned int y, std::string title_in = "Bunny Hop Designer") : window{sf::VideoMode{x, y}, title_in} {
}
designer_window::exit_code designer_window::run() {
    //    sf::RenderWindow window(sf::VideoMode(x, y), title);
    tgui::Gui gui(window);

    if (!active_menu) {
        active_menu = tgui::MenuBar::create();
        active_menu->addMenu("File");
        active_menu->addMenuItem("Load");
        active_menu->addMenuItem("Save");
        active_menu->addMenuItem("Exit");

        active_menu->addMenu("Tools");
        active_menu->addMenuItem("Settings");
        active_menu->addMenuItem("About");

        active_menu->connectMenuItem("File", "Load", []() { std::cout << "I need to have a load dialog :c Test\n"; });
        active_menu->connectMenuItem("File", "Save", []() { std::cout << "I need to make a save dialog :c \n"; });
        active_menu->connectMenuItem("File", "Exit", [=]() { window.close(); });

        active_menu->connectMenuItem("Tools", "Settings", []() { std::cout << "I need to make a Settings dialog\n"; });
        active_menu->connectMenuItem("Tools", "About", []() { std::cout << "Bunny Hop Engine made By Jim Marsden with the assistance of Insula, and Reversed Fool.\n"; });
    }

    gui.add(active_menu);
    gui.mainLoop();


    return exit_code::normal;
}
