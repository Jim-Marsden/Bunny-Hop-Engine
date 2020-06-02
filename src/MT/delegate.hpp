//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_DELEGATE_HPP
#define MOONLIGHT_TRAILS_DELEGATE_HPP

#include <tuple>
#include <vector>

namespace mt {

    template<class Callable_T>
    class delegate {
        std::vector<Callable_T> callables;

    public:
        delegate() = default;

        std::vector<Callable_T> const &operator+=(Callable_T const &Callable);

        template<class... Args_T>
        size_t operator()(Args_T &&... Args);

        [[nodiscard]] size_t GetSize() const;
    };

    template<class Callable_T>
    template<class... Args_T>
    size_t delegate<Callable_T>::operator()(Args_T &&... Args) {
        size_t result{};
        for (auto const &element : callables) {
            element(Args...);
            ++result;
        }
        return result;
    }

    template<class Callabl_Te>
    const std::vector<Callabl_Te> &
    delegate<Callabl_Te>::operator+=(const Callabl_Te &Callable) {
        callables.emplace_back(Callable);
        return callables;
    }

    template<class Callable_T>
    size_t delegate<Callable_T>::GetSize() const {
        return callables.size();
    }

} // namespace mt

#endif // MOONLIGHT_TRAILS_DELEGATE_HPP
