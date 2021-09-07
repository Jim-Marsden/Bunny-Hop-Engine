//
// Created by snizzfox on 5/16/20.
//

#include <iostream>
#include <bhe_core/SystemEvent.hpp>

#include <json/json.h>
#include <fstream>
#include <string_view>

sf::Keyboard::Key get_key(std::string_view const& Key)
{
	if (Key=="A" || Key=="a")
		return sf::Keyboard::A;
	else if (Key=="B" || Key=="b")
		return sf::Keyboard::B;
	else if (Key=="C" || Key=="c")
		return sf::Keyboard::C;
	else if (Key=="D" || Key=="d")
		return sf::Keyboard::D;
	else if (Key=="E" || Key=="e")
		return sf::Keyboard::E;
	else if (Key=="F" || Key=="f")
		return sf::Keyboard::F;
	else if (Key=="G" || Key=="g")
		return sf::Keyboard::G;
	else if (Key=="H" || Key=="h")
		return sf::Keyboard::H;
	else if (Key=="I" || Key=="i")
		return sf::Keyboard::I;
	else if (Key=="J" || Key=="j")
		return sf::Keyboard::J;
	else if (Key=="K" || Key=="k")
		return sf::Keyboard::K;
	else if (Key=="L" || Key=="l")
		return sf::Keyboard::L;
	else if (Key=="M" || Key=="m")
		return sf::Keyboard::M;
	else if (Key=="N" || Key=="n")
		return sf::Keyboard::N;
	else if (Key=="O" || Key=="o")
		return sf::Keyboard::O;
	else if (Key=="P" || Key=="p")
		return sf::Keyboard::P;
	else if (Key=="Q" || Key=="q")
		return sf::Keyboard::Q;
	else if (Key=="R" || Key=="r")
		return sf::Keyboard::R;
	else if (Key=="S" || Key=="s")
		return sf::Keyboard::S;
	else if (Key=="T" || Key=="t")
		return sf::Keyboard::T;
	else if (Key=="U" || Key=="u")
		return sf::Keyboard::U;
	else if (Key=="V" || Key=="v")
		return sf::Keyboard::V;
	else if (Key=="W" || Key=="w")
		return sf::Keyboard::W;
	else if (Key=="X" || Key=="x")
		return sf::Keyboard::X;
	else if (Key=="Y" || Key=="y")
		return sf::Keyboard::Y;
	else if (Key=="Z" || Key=="z")
		return sf::Keyboard::Z;
	else if (Key=="Space" || Key=="space" || Key==" ")
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

std::map<sf::Keyboard::Key, bhe::SystemEvent::MtKey> load_controls(std::string const& Json_File)
{
	Json::Value root;   // will contain the root value after parsing.
	std::ifstream stream(Json_File, std::ifstream::binary);
	stream >> root;

	return {
			{get_key(root["Up"].asString()), bhe::SystemEvent::MtKey::Up},
			{get_key(root["Down"].asString()), bhe::SystemEvent::MtKey::Down},
			{get_key(root["Left"].asString()), bhe::SystemEvent::MtKey::Left},
			{get_key(root["Right"].asString()), bhe::SystemEvent::MtKey::Right},
			{get_key(root["Jump"].asString()), bhe::SystemEvent::MtKey::Jump},
	};

}

bhe::SystemEvent::SystemEvent(sf::RenderWindow& window)
		:window{window}
{
	/*key_bindings[sf::Keyboard::Key::S] = MT_Key::Down;
	key_bindings[sf::Keyboard::Key::A] = MT_Key::Left;
	key_bindings[sf::Keyboard::Key::W] = MT_Key::Up;
	key_bindings[sf::Keyboard::Key::D] = MT_Key::Right;

	key_bindings[sf::Keyboard::Key::Space] = MT_Key::Jump;*/
	key_bindings = load_controls("Settings/Controls.json");
}

void bhe::SystemEvent::add_move_left(std::function<KeyboardFunctionType> const& Callable)
{
	move_left += Callable;
}

void bhe::SystemEvent::add_move_right(std::function<KeyboardFunctionType> const& Callable)
{
	move_right += Callable;
}

void bhe::SystemEvent::add_move_up(std::function<KeyboardFunctionType> const& Callable)
{
	move_up += Callable;
}

void bhe::SystemEvent::add_move_down(std::function<KeyboardFunctionType> const& Callable)
{
	move_down += Callable;
}

void bhe::SystemEvent::add_move_jump(std::function<KeyboardFunctionType> const& Callable)
{
	move_jump += Callable;
}

void bhe::SystemEvent::add_close(std::function<void()> const& Callable)
{
	close += Callable;
}

void bhe::SystemEvent::do_events()
{
	sf::Event event{};
	sf::FloatRect visible_area{};
	std::map<sf::Keyboard::Key, MtKey>::iterator iterator;
	while (window.pollEvent(event)) {
		switch (event.type) {

		case sf::Event::Closed:close();
			window.close();
			break;
		case sf::Event::Resized:visible_area = sf::FloatRect(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visible_area));
			break;
		case sf::Event::LostFocus:
		case sf::Event::GainedFocus:
		case sf::Event::TextEntered:break;
		case sf::Event::KeyPressed:if (key_bindings.find(event.key.code)==key_bindings.end()) break;

			if (key_bindings.at(event.key.code)==MtKey::Up) {
				move_up(true);
			}
			if (key_bindings.at(event.key.code)==MtKey::Left) {
				move_left(true);
			}
			if (key_bindings.at(event.key.code)==MtKey::Right) {
				move_right(true);
			}
			if (key_bindings.at(event.key.code)==MtKey::Down) {
				move_down(true);
			}
			if (key_bindings.at(event.key.code)==MtKey::Jump) {
				move_jump(true);
			}
			break;
		case sf::Event::KeyReleased:if (key_bindings.find(event.key.code)==key_bindings.end()) break;

			if (key_bindings.at(event.key.code)==MtKey::Up) {
				move_up(false);
			}
			if (key_bindings.at(event.key.code)==MtKey::Left) {
				move_left(false);
			}
			if (key_bindings.at(event.key.code)==MtKey::Right) {
				move_right(false);
			}
			if (key_bindings.at(event.key.code)==MtKey::Down) {
				move_down(false);
			}
			if (key_bindings.at(event.key.code)==MtKey::Jump) {
				move_jump(false);
			}
			break;
		case sf::Event::MouseWheelMoved:
		case sf::Event::MouseWheelScrolled:
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseMoved:
		case sf::Event::MouseEntered:
		case sf::Event::MouseLeft:
		case sf::Event::JoystickButtonPressed:
		case sf::Event::JoystickButtonReleased:
		case sf::Event::JoystickMoved:
		case sf::Event::JoystickConnected:
		case sf::Event::JoystickDisconnected:
		case sf::Event::TouchBegan:
		case sf::Event::TouchMoved:
		case sf::Event::TouchEnded:
		case sf::Event::SensorChanged:
		case sf::Event::Count:break;
		}
	}
}

