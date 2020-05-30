//
// Created by snizzfox on 5/16/20.
//

#include <iostream>
#include "SystemEvent.hpp"

#include <json/json.h>
#include <fstream>
#include <string_view>

sf::Keyboard::Key GetKey(std::string_view const &key) {
    if (key == "A" || key == "a")
        return sf::Keyboard::A;
    else if (key == "B" || key == "b")
        return sf::Keyboard::B;
    else if (key == "C" || key == "c")
        return sf::Keyboard::C;
    else if (key == "D" || key == "d")
        return sf::Keyboard::D;
    else if (key == "E" || key == "e")
        return sf::Keyboard::E;
    else if (key == "F" || key == "f")
        return sf::Keyboard::F;
    else if (key == "G" || key == "g")
        return sf::Keyboard::G;
    else if (key == "H" || key == "h")
        return sf::Keyboard::H;
    else if (key == "I" || key == "i")
        return sf::Keyboard::I;
    else if (key == "J" || key == "j")
        return sf::Keyboard::J;
    else if (key == "K" || key == "k")
        return sf::Keyboard::K;
    else if (key == "L" || key == "l")
        return sf::Keyboard::L;
    else if (key == "M" || key == "m")
        return sf::Keyboard::M;
    else if (key == "N" || key == "n")
        return sf::Keyboard::N;
    else if (key == "O" || key == "o")
        return sf::Keyboard::O;
    else if (key == "P" || key == "p")
        return sf::Keyboard::P;
    else if (key == "Q" || key == "q")
        return sf::Keyboard::Q;
    else if (key == "R" || key == "r")
        return sf::Keyboard::R;
    else if (key == "S" || key == "s")
        return sf::Keyboard::S;
    else if (key == "T" || key == "t")
        return sf::Keyboard::T;
    else if (key == "U" || key == "u")
        return sf::Keyboard::U;
    else if (key == "V" || key == "v")
        return sf::Keyboard::V;
    else if (key == "W" || key == "w")
        return sf::Keyboard::W;
    else if (key == "X" || key == "x")
        return sf::Keyboard::X;
    else if (key == "Y" || key == "y")
        return sf::Keyboard::Y;
    else if (key == "Z" || key == "z")
        return sf::Keyboard::Z;
    else if (key == "Space" || key == "space" || key == " ")
        return sf::Keyboard::Space;
    else
        return sf::Keyboard::Unknown;

    /* Unknown = -1, A = 0, B, C,
  D, E, F, G,
  H, I, J, K,
  L, M, N, O,
  P, Q, R, S,
  T, U, V, W,
  X, Y, Z, Num0,
  Num1, Num2, Num3, Num4,
  Num5, Num6, Num7, Num8,
  Num9, Escape, LControl, LShift,
  LAlt, LSystem, RControl, RShift,
  RAlt, RSystem, Menu, LBracket,
  RBracket, Semicolon, Comma, Period,
  Quote, Slash, Backslash, Tilde,
  Equal, Hyphen, Space, Enter,
  Backspace, Tab, PageUp, PageDown,
  End, Home, Insert, Delete,
  Add, Subtract, Multiply, Divide,
  Left, Right, Up, Down,
  Numpad0, Numpad1, Numpad2, Numpad3,
  Numpad4, Numpad5, Numpad6, Numpad7,
  Numpad8, Numpad9, F1, F2,
  F3, F4, F5, F6,
  F7, F8, F9, F10,
  F11, F12, F13, F14,
  F15, Pause, KeyCount, Dash = Hyphen,
  BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter
}*/
}

std::map<sf::Keyboard::Key, mt::SystemEvent::MT_Key> Load_Controls(std::string const &json_file) {
    Json::Value root;   // will contain the root value after parsing.
    std::ifstream stream(json_file, std::ifstream::binary);
    stream >> root;


    return {
            {GetKey(root["Up"].asString()),    mt::SystemEvent::MT_Key::Up},
            {GetKey(root["Down"].asString()),  mt::SystemEvent::MT_Key::Down},
            {GetKey(root["Left"].asString()),  mt::SystemEvent::MT_Key::Left},
            {GetKey(root["Right"].asString()), mt::SystemEvent::MT_Key::Right},
            {GetKey(root["Jump"].asString()),  mt::SystemEvent::MT_Key::Jump},
    };


}

mt::SystemEvent::SystemEvent(sf::RenderWindow &window_in, mt::player &Player_1) : window{window_in}, player{Player_1} {
    /*key_bindings[sf::Keyboard::Key::S] = MT_Key::Down;
    key_bindings[sf::Keyboard::Key::A] = MT_Key::Left;
    key_bindings[sf::Keyboard::Key::W] = MT_Key::Up;
    key_bindings[sf::Keyboard::Key::D] = MT_Key::Right;

    key_bindings[sf::Keyboard::Key::Space] = MT_Key::Jump;*/
    key_bindings = Load_Controls("Settings/Controls.json");
}

void mt::SystemEvent::AddMoveLeft(std::function<keyboardFunctionType> const &Callable) {
    move_left += Callable;
}

void mt::SystemEvent::AddMoveRight(std::function<keyboardFunctionType> const &Callable) {
    move_right += Callable;
}

void mt::SystemEvent::AddMoveUp(std::function<keyboardFunctionType> const &Callable) {
    move_up += Callable;
}

void mt::SystemEvent::AddMoveDown(std::function<keyboardFunctionType> const &Callable) {
    move_down += Callable;
}

void mt::SystemEvent::AddMoveJump(std::function<keyboardFunctionType> const &Callable) {
    move_jump += Callable;
}

void mt::SystemEvent::AddClose(std::function<void()> const &Callable) {
    close += Callable;
}

void mt::SystemEvent::DoEvents() {
    sf::Event event{};
    sf::FloatRect visible_area{};
    std::map<sf::Keyboard::Key, MT_Key>::iterator iterator;
    while (window.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed:
                close();
                window.close();
                break;
            case sf::Event::Resized:
                visible_area = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visible_area));
                break;
            case sf::Event::LostFocus:

                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                if (key_bindings.find(event.key.code) == key_bindings.end()) break;


                if (key_bindings.at(event.key.code) == MT_Key::Up) {
                    move_up(player, true);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Left) {
                    move_left(player, true);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Right) {
                    move_right(player, true);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Down) {
                    move_down(player, true);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Jump) {
                    move_jump(player, true);
                }
                break;
            case sf::Event::KeyReleased:
                if (key_bindings.find(event.key.code) == key_bindings.end()) break;

                if (key_bindings.at(event.key.code) == MT_Key::Up) {
                    move_up(player, false);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Left) {
                    move_left(player, false);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Right) {
                    move_right(player, false);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Down) {
                    move_down(player, false);
                }
                if (key_bindings.at(event.key.code) == MT_Key::Jump) {
                    move_jump(player, false);
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

