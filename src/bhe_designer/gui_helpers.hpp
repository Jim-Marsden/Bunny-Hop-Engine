//
// Created by james on 7/28/2021.
//

#ifndef BUNNY_HOP_CORE_GUI_HELPERS_HPP
#define BUNNY_HOP_CORE_GUI_HELPERS_HPP

#include <TGUI/TGUI.hpp>
#include <filesystem>


namespace bhe::designer{
    //creates a default menubar unless it needs something else
    tgui::MenuBar::Ptr default_menubar(sf::RenderWindow & window, tgui::Gui & gui);

    //Handles save/load pathes with an out peram...for now.
    tgui::ChildWindow::Ptr file_dialog(std::filesystem::path & out_path, bool save_mode = false);

    tgui::ChildWindow::Ptr settings_dialog();

    tgui::ChildWindow::Ptr about_dialog();

} // namespace bhe::designer

#endif//BUNNY_HOP_CORE_GUI_HELPERS_HPP
