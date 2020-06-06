//
// Created by snizzfox on 5/16/20.
//

#ifndef BUNNY_HOP_ENGINE_DELEGATE_HPP
#define BUNNY_HOP_ENGINE_DELEGATE_HPP

#include <tuple>
#include <vector>
#include <functional>

namespace bhe {

    template<class Callable_T>
    class delegate {
        std::vector<Callable_T> _callables;

    public:
        delegate() = default;

        std::vector<Callable_T> const &operator+=(Callable_T const &Callable);

        template<class... Args_T>
        constexpr auto operator()(Args_T &&... Args) const;

        [[nodiscard]] size_t GetSize() const;
    };


    template<class Callabl_Te>
    const std::vector<Callabl_Te> &
    delegate<Callabl_Te>::operator+=(const Callabl_Te &Callable) {
        _callables.emplace_back(Callable);
        return _callables;
    }

    template<class Callable_T>
    size_t delegate<Callable_T>::GetSize() const {
        return _callables.size();
    }

    template<class Callable_T>
    template<class... Args_T>
    constexpr auto delegate<Callable_T>::operator()(Args_T &&... Args) const {
        if constexpr(!std::is_void<decltype(std::invoke(_callables[0], Args ...))>::value) {
            if (!_callables.empty()) {
                auto first_element = _callables.cbegin();
                auto result = std::invoke(*first_element, Args ...);
                for (; first_element != _callables.cend(); ++first_element)std::invoke(*first_element, Args ...);
                return result;
            }
        } else {
            for (auto const &element : _callables) {
                std::invoke(element, Args...);
            }
        }
    }

} // namespace bhe

#endif // BUNNY_HOP_ENGINE_DELEGATE_HPP
