//
// Created by james on 7/28/2021.
//

#include "gui_helpers.hpp"
#include <iostream>
tgui::MenuBar::Ptr bhe::designer::default_menubar(sf::RenderWindow & window, tgui::Gui & gui) {
    auto active_menu = tgui::MenuBar::create();
    active_menu->addMenu("File");
    active_menu->addMenuItem("Load");
    active_menu->addMenuItem("Save");
    active_menu->addMenuItem("Exit");

    active_menu->addMenu("Tools");
    active_menu->addMenuItem("Settings");
    active_menu->addMenuItem("About");

    active_menu->connectMenuItem("File", "Load", [](){ std::cout << "I need to have a load dialog :c Test\n"; });
    active_menu->connectMenuItem("File", "Save", []() { std::cout << "I need to make a save dialog :c \n"; });
    active_menu->connectMenuItem("File", "Exit", [&window]() {window.close(); });

    active_menu->connectMenuItem("Tools", "Settings", []() { std::cout << "I need to make a Settings dialog\n"; });
    active_menu->connectMenuItem("Tools", "About", [&gui]() {gui.add(bhe::designer::about_dialog());});// std::cout << "Bunny Hop Engine made By Jim Marsden with the assistance of Insula, and Reversed Fool.\n"; });

    return active_menu;
}
tgui::ChildWindow::Ptr bhe::designer::about_dialog() {
    auto window = tgui::ChildWindow::create("About");
    auto l = tgui::Label::create();
    l->setText("Bunny Hop Engine made By:\n Jim Marsden with the assistance of Insula, and Reversed Fool.");

    window->add(l);
    return window;


}
