//
// Created by snizzfox on 5/16/20.
//

#ifndef BUNNY_HOP_CORE_SYSTEMEVENT_HPP
#define BUNNY_HOP_CORE_SYSTEMEVENT_HPP

#include <bhe_core/Delegate.hpp>
#include <bhe_core/player.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

namespace bhe {

class SystemEvent {
public:
	enum class MtKey {
		None,
		Up,
		Down,
		Left,
		Right,
		Jump,
	};
	using KeyboardFunctionType = void(bool);
	using KeyboardDelegateType =
	Delegate<std::function<KeyboardFunctionType>>;
protected:
	std::map<sf::Keyboard::Key, MtKey> key_bindings;
	KeyboardDelegateType move_left;
	KeyboardDelegateType move_right;
	KeyboardDelegateType move_up;
	KeyboardDelegateType move_down;

	KeyboardDelegateType move_jump;

	Delegate<std::function<void()>> close;

	sf::RenderWindow& window;
	//player &_player;

public:
	SystemEvent() = delete;

	SystemEvent(SystemEvent const&) = delete;

	SystemEvent(SystemEvent&&) = delete;

	~SystemEvent() = default;

	SystemEvent& operator=(SystemEvent&&) = delete;

	SystemEvent& operator=(SystemEvent const&) = delete;

	explicit SystemEvent(sf::RenderWindow& window);

	void add_move_left(std::function<KeyboardFunctionType> const& Callable);

	void add_move_right(std::function<KeyboardFunctionType> const& Callable);

	void add_move_up(std::function<KeyboardFunctionType> const& Callable);

	void add_move_down(std::function<KeyboardFunctionType> const& Callable);

	void add_move_jump(std::function<KeyboardFunctionType> const& Callable);

	void add_close(std::function<void()> const& Callable);

	void do_events();

};
}

#endif //BUNNY_HOP_CORE_SYSTEMEVENT_HPP
