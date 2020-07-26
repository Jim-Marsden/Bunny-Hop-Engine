//
// Created by snizzfox on 6/6/20.
//
#include <iostream>
#include <bhe_designer/windowManager.hpp>

int main() {
    windowManager window_manager;
    auto[result, message] = window_manager.Run();
    std::cout << "result: " << (result ? "true" : "false") << "\tmessage: " << static_cast<int>(message) << '\n';
    return 0;
}