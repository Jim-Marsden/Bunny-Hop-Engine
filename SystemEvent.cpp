//
// Created by snizzfox on 5/16/20.
//

#include <iostream>
#include "SystemEvent.hpp"

SystemEvent::SystemEvent(sf::RenderWindow &window_in, Player & player1) : window{window_in}, player{player1}{
    key_bindings[sf::Keyboard::Key::S] = MT_Key::Down;
    key_bindings[sf::Keyboard::Key::A] = MT_Key::Left;
    key_bindings[sf::Keyboard::Key::W] = MT_Key::Up;
    key_bindings[sf::Keyboard::Key::D] = MT_Key::Right;

    key_bindings[sf::Keyboard::Key::Space] = MT_Key::Jump;
}

void SystemEvent::AddMoveLeft(std::function<KeyboardFunctionType> const & callable){
    MoveLeft += callable;
}

void SystemEvent::AddMoveRight(std::function<KeyboardFunctionType> const & callable){
    MoveRight += callable;
}

void SystemEvent::AddMoveUp(std::function<KeyboardFunctionType> const & callable){
    MoveUp+= callable;
}

void SystemEvent::AddMoveDown(std::function<KeyboardFunctionType> const & callable){
    MoveDown += callable;
}

void SystemEvent::AddMoveJump(std::function<KeyboardFunctionType> const & callable){
    MoveJump += callable;
}

void SystemEvent::AddClose(std::function<void()> const & callable) {
    Close += callable;
}

void SystemEvent::DoEvents() {
    sf::Event event{};
    sf::FloatRect visibleArea{};
    std::map<sf::Keyboard::Key, MT_Key>::iterator iterator;
    while(window.pollEvent(event)){
        switch (event.type) {

            case sf::Event::Closed:
                Close();
                window.close();
                break;
            case sf::Event::Resized:
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                break;
            case sf::Event::LostFocus:

                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                if(key_bindings.find(event.key.code) == key_bindings.end()) break;


                if(key_bindings.at(event.key.code) == MT_Key::Up){
                    MoveUp(player, true);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Left){
                    MoveLeft(player, true);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Right){
                    MoveRight(player, true);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Down){
                    MoveDown(player, true);
                }
                if(key_bindings.at( event.key.code) == MT_Key::Jump){
                    MoveJump(player, true);
                }
                break;
            case sf::Event::KeyReleased:
                if(key_bindings.find(event.key.code) == key_bindings.end()) break;

                if(key_bindings.at(event.key.code) == MT_Key::Up){
                    MoveUp(player, false);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Left){
                    MoveLeft(player, false);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Right){
                    MoveRight(player, false);
                }
                if(key_bindings.at(event.key.code) == MT_Key::Down){
                    MoveDown(player, false);
                }
                if(key_bindings.at( event.key.code) == MT_Key::Jump){
                    MoveJump(player, false);
                }
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseEntered:
                break;
            case sf::Event::MouseLeft:
                break;
            case sf::Event::JoystickButtonPressed:
                break;
            case sf::Event::JoystickButtonReleased:
                break;
            case sf::Event::JoystickMoved:
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::TouchBegan:
                break;
            case sf::Event::TouchMoved:
                break;
            case sf::Event::TouchEnded:
                break;
            case sf::Event::SensorChanged:
                break;
            case sf::Event::Count:
                break;
        }
    }
}

