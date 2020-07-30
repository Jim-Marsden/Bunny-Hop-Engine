//
// Created by snizzfox on 5/16/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_SYSTEMEVENT_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_SYSTEMEVENT_HPP

#include <bhe_core/delegate.hpp>
#include <bhe_core/player.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

namespace bhe {


    class systemEvent {
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
        delegate<std::function<KeyboardFunctionType>>;
    protected:
        std::map<sf::Keyboard::Key, MtKey> key_bindings_;
        KeyboardDelegateType move_left_;
        KeyboardDelegateType move_right_;
        KeyboardDelegateType move_up_;
        KeyboardDelegateType move_down_;


        KeyboardDelegateType move_jump_;

        delegate<std::function<void()>> close_;

        sf::RenderWindow &window_;
        //player &_player;

    public:
        systemEvent() = delete;

        systemEvent(systemEvent const &) = delete;

        systemEvent(systemEvent &&) = delete;

        ~systemEvent() = default;

        systemEvent &operator=(systemEvent &&) = delete;

        systemEvent &operator=(systemEvent const &) = delete;

        explicit systemEvent(sf::RenderWindow &Window);

        void AddMoveLeft(std::function<KeyboardFunctionType> const &Callable);

        void AddMoveRight(std::function<KeyboardFunctionType> const &Callable);

        void AddMoveUp(std::function<KeyboardFunctionType> const &Callable);

        void AddMoveDown(std::function<KeyboardFunctionType> const &Callable);

        void AddMoveJump(std::function<KeyboardFunctionType> const &Callable);

        void AddClose(std::function<void()> const &Callable);

        void DoEvents();

    };
}


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_SYSTEMEVENT_HPP
