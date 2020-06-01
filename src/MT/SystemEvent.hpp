//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_SYSTEMEVENT_HPP
#define MOONLIGHT_TRAILS_SYSTEMEVENT_HPP

#include "delegate.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

namespace mt {

    class player;

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
        using keyboardFunctionType = void(mt::player &, bool);
        using keyboardDelegateType =
        delegate<std::function<keyboardFunctionType>>;
    protected:
        std::map<sf::Keyboard::Key, MtKey> _key_bindings;
        keyboardDelegateType _move_left;
        keyboardDelegateType _move_right;
        keyboardDelegateType _move_up;
        keyboardDelegateType _move_down;


        keyboardDelegateType _move_jump;

        delegate<std::function<void()>> _close;

        sf::RenderWindow &_window;
        player &_player;

    public:
        SystemEvent() = delete;

        explicit SystemEvent(sf::RenderWindow &Window, mt::player &Player_1);

        void AddMoveLeft(std::function<keyboardFunctionType> const &Callable);

        void AddMoveRight(std::function<keyboardFunctionType> const &Callable);

        void AddMoveUp(std::function<keyboardFunctionType> const &Callable);

        void AddMoveDown(std::function<keyboardFunctionType> const &Callable);

        void AddMoveJump(std::function<keyboardFunctionType> const &Callable);

        void AddClose(std::function<void()> const &Callable);

        void DoEvents();

    };
}


#endif //MOONLIGHT_TRAILS_SYSTEMEVENT_HPP