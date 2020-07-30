//
// Created by snizzfos on 5/22/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_STATE_MACHINE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_STATE_MACHINE_HPP

#include <utility>
#include <array>

namespace bhe {

    template<class Enumerator_T, class Function_T, int array_size = 0xf>
    class stateMachine {
    public:

    protected:
        std::array<std::pair<Enumerator_T, Function_T>, array_size> states_;
    public:
        constexpr stateMachine() = default;

        constexpr ~stateMachine() = default;

        constexpr stateMachine(stateMachine const &) = default;

        constexpr stateMachine(stateMachine &&)  noexcept = default;

        constexpr stateMachine &operator=(stateMachine &&)  noexcept = default;

        constexpr stateMachine &operator=(stateMachine const &) = default;


        constexpr Function_T &operator[](Enumerator_T const &Enumerator);

        constexpr Function_T &operator[](int Index);

        constexpr bool Add(Enumerator_T const &Enumerator, Function_T const &Callable);

    };


    template<class Enumerator_T, class Function, int array_size>
    constexpr bool
    stateMachine<Enumerator_T, Function, array_size>::Add(Enumerator_T const &Enumerator, Function const &Callable) {
        for (auto &element: states_) {
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
        if (Index >= states_.size()) {
            return states_.front();

        }
    }


    template<class Enumerator_T, class Function, int array_size>
    constexpr Function &stateMachine<Enumerator_T, Function, array_size>::operator[](Enumerator_T const &Enumerator) {
        for (auto &element: states_) {
            if (element.first == Enumerator)return element.second;
        }
        return states_.front().second;
    }
} //namespace bhe
#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_STATE_MACHINE_HPP
