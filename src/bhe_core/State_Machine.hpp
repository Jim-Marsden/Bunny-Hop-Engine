//
// Created by Jim Marsden on 5/22/20.
//

#ifndef BUNNY_HOP_CORE_STATE_MACHINE_HPP
#define BUNNY_HOP_CORE_STATE_MACHINE_HPP

#include <utility>
#include <array>

namespace bhe {

    template<class Enumerator_T, class Function_T, int array_size = 0xf>
    class StateMachine {
    public:

    protected:
        std::array<std::pair<Enumerator_T, Function_T>, array_size> states;
    public:
        constexpr StateMachine() = default;

        ~StateMachine() = default;

        constexpr StateMachine(StateMachine const &) = default;

        constexpr StateMachine(StateMachine &&)  noexcept = default;

        constexpr StateMachine &operator=(StateMachine &&)  noexcept = default;

        constexpr StateMachine &operator=(StateMachine const &) = default;


        constexpr Function_T &operator[](Enumerator_T const &enumerator);

        constexpr Function_T &operator[](int index);

        constexpr auto get_size() noexcept;

        constexpr bool add(Enumerator_T const &enumerator, Function_T const &callable);

        constexpr auto begin() noexcept;

        constexpr auto end()noexcept;

        constexpr auto cbegin()noexcept;
        constexpr auto cend()noexcept;



    };


    template<class Enumerator_T, class Function, int array_size>
    constexpr bool
    StateMachine<Enumerator_T, Function, array_size>::add(Enumerator_T const &enumerator, Function const &callable) {
        for (auto &[key, value]: states) {
            if (!value) {
                key = enumerator;
                value = callable;
                return true;
            }
        }
        return false;
    }


    template<class Enumerator_T, class Function, int array_size>
    constexpr Function &StateMachine<Enumerator_T, Function, array_size>::operator[](int index) {
        if (index >= states.size()) {
            return states.front();

        }
    }


    template<class Enumerator_T, class Function, int array_size>
    constexpr Function &StateMachine<Enumerator_T, Function, array_size>::operator[](Enumerator_T const &enumerator) {
        for (auto &element: states) {
            if (element.first == enumerator)return element.second;
        }
        return states.front().second;
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto StateMachine<Enumerator_T, Function_T, array_size>::begin() noexcept {
        return states.begin();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto StateMachine<Enumerator_T, Function_T, array_size>::end() noexcept {
        return states.end();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto StateMachine<Enumerator_T, Function_T, array_size>::cbegin() noexcept {
        return states.cbegin();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto StateMachine<Enumerator_T, Function_T, array_size>::cend() noexcept {
        return states.cend();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto StateMachine<Enumerator_T, Function_T, array_size>::get_size() noexcept {
        return array_size;
    }


} //namespace bhe
#endif //BUNNY_HOP_CORE_STATE_MACHINE_HPP
