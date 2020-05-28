//
// Created by snizzfos on 5/22/20.
//

#ifndef MOONLIGHT_TRAILS_STATE_MACHINE_H
#define MOONLIGHT_TRAILS_STATE_MACHINE_H
#include <utility>
#include <array>

 namespace MT {

    template<class Enumerator, class Function, int array_size = 0xf>
    class StateMachine {
    public:

    protected:
        std::array <std::pair<Enumerator, Function>, array_size> _states;
    public:
        constexpr StateMachine() = default;


        constexpr Function &operator[](Enumerator const &enumerator);

        constexpr Function &operator[](int index);

        constexpr bool add(Enumerator const &enumerator, Function const &callable);

    };


    template<class Enumerator, class Function, int array_size>
    constexpr bool StateMachine<Enumerator, Function, array_size>::add(Enumerator const &enumerator, Function const &callable) {
        for (auto &element: _states) {
            if (!element.second) {
                element.first = enumerator;
                element.second = callable;
                return true;
            }
        }
        return false;
    }



    template<class Enumerator, class Function, int array_size>
    constexpr Function & StateMachine<Enumerator, Function, array_size>::operator[](int index) {
        if (index >= _states.size()) {
            return _states.front();

        }
    }



    template<class Enumerator, class Function, int array_size>
    constexpr Function & StateMachine<Enumerator, Function, array_size>::operator[](Enumerator const &enumerator) {
        for (auto &element: _states) {
            if (element.first == enumerator)return element.second;
        }
        return _states.front().second;
    }
} //namespace MT
#endif //MOONLIGHT_TRAILS_STATE_MACHINE_H
