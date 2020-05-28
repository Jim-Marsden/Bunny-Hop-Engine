//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_SYSTEMEVENT_HPP
#define MOONLIGHT_TRAILS_SYSTEMEVENT_HPP



#include "Delegate.hpp"
#include <functional>
#include <map>
#include <SFML/Graphics.hpp>

namespace MT {

    class Player;

    class SystemEvent {
    public:
        enum class MT_Key{
            None,
            Up,
            Down,
            Left,
            Right,
            Jump,
        };
        using KeyboardFunctionType = void(MT::Player&, bool);
        using KeyboardDelegateType = Delegate<std::function <KeyboardFunctionType>>;
    protected:
        std::map<sf::Keyboard::Key, MT_Key> key_bindings;
        KeyboardDelegateType MoveLeft;
        KeyboardDelegateType MoveRight;
        KeyboardDelegateType MoveUp;
        KeyboardDelegateType MoveDown;


        KeyboardDelegateType MoveJump;

        Delegate<std::function<void()>> Close;

        sf::RenderWindow &window;
        Player &player;

    public:
        SystemEvent() = delete;
        explicit SystemEvent(sf::RenderWindow & window, Player &player);

        void AddMoveLeft(std::function<KeyboardFunctionType> const & callable);
        void AddMoveRight(std::function<KeyboardFunctionType> const & callablecallable);

        void AddMoveUp(std::function<KeyboardFunctionType> const & callable);
        void AddMoveDown(std::function<KeyboardFunctionType> const & callable);

        void AddMoveJump(std::function<KeyboardFunctionType> const & callable);

        void AddClose(std::function<void()>const & callable);

        void DoEvents();

    };
}


#endif //MOONLIGHT_TRAILS_SYSTEMEVENT_HPP
