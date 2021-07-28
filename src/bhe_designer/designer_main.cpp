//
// Created by Jim Marsden on 6/6/20.
//
#include <bhe_designer/windowManager.hpp>
#include <iostream>
#include "designer_window.h"

//Do I really want to keep this style of ugly gui interface? All the objects, etc?
/* TODO:
 * 1) Change to have a single window_manager class that will have an overall layout, that can take "Mode"
 *      structs that follow a class layout with everything that isn't menu bar and status bar
 * 2) Have a menu bar and a status bar
 * 3) extend out features and modes with 1) and use that as a primary tool for expansion
 */


int main(){
    designer_window window{800, 400, "title"};
    window.run();

    return {};
}