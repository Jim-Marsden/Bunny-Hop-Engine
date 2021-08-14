//
// Created by Jim Marsden on 6/6/20.
//
#include "designerWindow.h"
#include "gui_modes.hpp"
#include <bhe_designer/windowManager.hpp>
#include <iostream>

//Do I really want to keep this style of ugly gui interface? All the objects, etc?
/* TODO:
 * 1) Change to have a single window_manager class that will have an overall layout, that can take "Mode"
 *      structs that follow a class layout with everything that isn't menu bar and status bar
 * 2) Have a menu bar and a status bar
 * 3) extend out features and modes with 1) and use that as a primary tool for expansion
 */


int main(){
    bhe::designer::gui_modes m1{.mode_name{L"Hai!"} };

    m1.to_draw.emplace_back(tgui::Label::create("stuff, stuff, stuff, more stuff!"));

    designerWindow window{800, 400, "title"};
    window.run();

    return {};
}