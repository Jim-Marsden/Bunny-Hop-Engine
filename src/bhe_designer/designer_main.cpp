//
// Created by snizzfox on 6/6/20.
//
#include <iostream>
#include <bhe_designer/windowManager.hpp>


/* TODO:
 * 1) Window manager
 * 2) Paine elements that hold buttons, and interface objects
 * 2-a) should work on a way to have the dockable and drag and dropable
 * 3) Renderer object that renders onto a sfml render texture
 *
 */

int main() {
    windowManager window_manager;
    auto[result, message] = window_manager.Run();
    std::cout << "result: " << (result ? "true" : "false") << "\tmessage: " << static_cast<int>(message) << '\n';
    return 0;
}