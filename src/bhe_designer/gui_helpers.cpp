//
// Created by james on 7/28/2021.
//

#include "gui_helpers.hpp"
#include <iostream>

static bool save_load_in_use{false};
tgui::MenuBar::Ptr bhe::designer::default_menubar(sf::RenderWindow &window, tgui::Gui &gui) {
    auto active_menu = tgui::MenuBar::create();
    active_menu->addMenu("File");
    active_menu->addMenuItem("Load");
    active_menu->addMenuItem("Save");
    active_menu->addMenuItem("Exit");

    active_menu->addMenu("Tools");
    active_menu->addMenuItem("Settings");
    active_menu->addMenuItem("About");

    active_menu->connectMenuItem("File", "Load", [&gui]() {
        std::filesystem::path p{};
        auto v{bhe::designer::file_dialog(p, save_load_in_use, false)};
        if (v) gui.add(v);
        else
            std::cout << "Load/Save already open!\n";
    });
    active_menu->connectMenuItem("File", "Save", [&gui]() {
        std::filesystem::path p{};
        auto v{bhe::designer::file_dialog(p, save_load_in_use, true)};
        if (v) gui.add(v);
        else
            std::cout << "Load/Save already open!\n";

        std::cout << "I need to make a save dialog :c \n";
    });
    active_menu->connectMenuItem("File", "Exit", [&window]() { window.close(); });

    active_menu->connectMenuItem("Tools", "Settings", [&gui]() { gui.add(bhe::designer::settings_dialog()); });
    active_menu->connectMenuItem("Tools", "About", [&gui]() { gui.add(bhe::designer::about_dialog()); });// std::cout << "Bunny Hop Engine made By Jim Marsden with the assistance of Insula, and Reversed Fool.\n"; });

    return active_menu;
}
tgui::ChildWindow::Ptr bhe::designer::about_dialog() {
    auto window = tgui::ChildWindow::create("About");
    auto l = tgui::Label::create();
    l->setText("Bunny Hop Engine made By:\n Jim Marsden with the assistance of Insula, and Reversed Fool.");

    window->add(l);
    return window;
}
tgui::ChildWindow::Ptr bhe::designer::settings_dialog() {
    auto window = tgui::ChildWindow::create("settings");

    window->add(tgui::Label::create("Place holder text :c"));
    return window;
}
tgui::ChildWindow::Ptr bhe::designer::file_dialog(std::filesystem::path &out_path, bool &lock, bool save_mode) {
    if (!lock) {
        lock = true;
        auto window = tgui::ChildWindow::create("Filebox");
        if (save_mode) window->add(tgui::Label::create("Placeholder(save mode)..... :c"));
        else
            window->add(tgui::Label::create("Placeholder(load mode)..... :c"));
        window->onClose([&lock]() { lock = false; });
        return window;
    } else
        return nullptr;
}
