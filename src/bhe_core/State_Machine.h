//
// Created by snizzfos on 5/22/20.
//

#ifndef MOONLIGHT_TRAILS_STATE_MACHINE_H
#define MOONLIGHT_TRAILS_STATE_MACHINE_H

#include <utility>
#include <array>

namespace bhe {

    template<class Enumerator_T, class Function_T, int array_size = 0xf>
    class stateMachine {
    public:

    protected:
        std::array<std::pair<Enumerator_T, Function_T>, array_size> states;
    public:
        constexpr stateMachine() = default;


        constexpr Function_T &operator[](Enumerator_T const &Enumerator);

        constexpr Function_T &operator[](int Index);

        constexpr bool add(Enumerator_T const &Enumerator, Function_T const &Callable);

    };


    template<class Enumerator_T, class Function, int array_size>
    constexpr bool
    stateMachine<Enumerator_T, Function, array_size>::add(Enumerator_T const &Enumerator, Function const &Callable) {
        for (auto &element: states) {
            if (!element.second) {
                element.first = Enumerator;
                element.second = Callable;
                return true;
            }
        }
        return false;
    }


    template<class Enumerator_T, class Function, int array_size>
    constexpr Function &stateMachine<Enumerator_T, Function, array_size>::operator[](int Index) {
        if (Index >= states.size()) {
            return states.front();

        }
    }


    template<class Enumerator_T, class Function, int array_size>
    constexpr Function &stateMachine<Enumerator_T, Function, array_size>::operator[](Enumerator_T const &Enumerator) {
        for (auto &element: states) {
            if (element.first == Enumerator)return element.second;
        }
        return states.front().second;
    }
} //namespace bhe
#endif //MOONLIGHT_TRAILS_STATE_MACHINE_H
