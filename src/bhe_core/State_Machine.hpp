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

        ~stateMachine() = default;

        constexpr stateMachine(stateMachine const &) = default;

        constexpr stateMachine(stateMachine &&)  noexcept = default;

        constexpr stateMachine &operator=(stateMachine &&)  noexcept = default;

        constexpr stateMachine &operator=(stateMachine const &) = default;


        constexpr Function_T &operator[](Enumerator_T const &Enumerator);

        constexpr Function_T &operator[](int Index);

        constexpr auto get_size() noexcept;

        constexpr bool add(Enumerator_T const &Enumerator, Function_T const &Callable);

        constexpr auto begin() noexcept;

        constexpr auto end()noexcept;

        constexpr auto cbegin()noexcept;
        constexpr auto cend()noexcept;



    };


    template<class Enumerator_T, class Function, int array_size>
    constexpr bool
    stateMachine<Enumerator_T, Function, array_size>::add(Enumerator_T const &Enumerator, Function const &Callable) {
        for (auto &[key, value]: states_) {
            if (!value) {
                key = Enumerator;
                value = Callable;
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
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto stateMachine<Enumerator_T, Function_T, array_size>::begin() noexcept {
        return states_.begin();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto stateMachine<Enumerator_T, Function_T, array_size>::end() noexcept {
        return states_.end();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto stateMachine<Enumerator_T, Function_T, array_size>::cbegin() noexcept {
        return states_.cbegin();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto stateMachine<Enumerator_T, Function_T, array_size>::cend() noexcept {
        return states_.cend();
    }
    template<class Enumerator_T, class Function_T, int array_size>
    constexpr auto stateMachine<Enumerator_T, Function_T, array_size>::get_size() noexcept {
        return array_size;
    }


} //namespace bhe
#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_STATE_MACHINE_HPP
