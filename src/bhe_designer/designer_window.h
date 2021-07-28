//
// Created by Jim Marsden on 7/25/2021.
//

#ifndef BUNNY_HOP_CORE_DESIGNER_WINDOW_H
#define BUNNY_HOP_CORE_DESIGNER_WINDOW_H

#include <TGUI/TGUI.hpp>
#include <string>


class designer_window {
protected:
    tgui::MenuBar::Ptr active_menu;
    sf::RenderWindow window;

public:
    enum struct exit_code{
        normal = 0,
        null_function,
        function_failed,
    };

    designer_window() = delete;
    designer_window(unsigned int x, unsigned int y, std::string title);
    designer_window(designer_window const&) =delete;
    designer_window(designer_window &&) = delete;

    designer_window & operator=(designer_window const &) = delete;

    ~designer_window() = default;


    exit_code run();

};


#endif//BUNNY_HOP_CORE_DESIGNER_WINDOW_H
