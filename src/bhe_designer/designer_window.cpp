//
// Created by james on 7/25/2021.
//

#include "designer_window.h"
#include <utility>
designer_window::designer_window(unsigned int x, unsigned int y, char const *title) : x{x}, y{y}, title{title} {

}
designer_window::exit_code designer_window::run() {
    sf::RenderWindow window{sf::VideoMode{x, y}, title};

    tgui::Gui gui{window};


    return exit_code::normal;
}
