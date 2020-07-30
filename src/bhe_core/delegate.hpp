//
// Created by snizzfox on 5/16/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_DELEGATE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_DELEGATE_HPP

#include <tuple>
#include <vector>
#include <functional>

namespace bhe {

    template<class Callable_T>
    class delegate {
        std::vector<Callable_T> callables_;

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
        callables_.emplace_back(Callable);
        return callables_;
    }

    template<class Callable_T>
    size_t delegate<Callable_T>::GetSize() const {
        return callables_.size();
    }

    template<class Callable_T>
    template<class... Args_T>
    constexpr auto delegate<Callable_T>::operator()(Args_T &&... Args) const {
        if constexpr(!std::is_void<decltype(std::invoke(callables_[0], Args ...))>::value) {
            using ResultT = decltype(std::invoke(callables_[0], Args ...));


            if (!callables_.empty()) {

                ResultT result;
                bool skip_first = true;

                for (auto const &function : callables_) {
                    if (skip_first) {
                        skip_first = false;
                        result = std::invoke(function, Args ...);
                    }
                    std::invoke(function, Args ...);
                }
                return result;
            }
            return decltype(std::invoke(callables_[0], Args ...)){};
        } else {
            for (auto const &element : callables_) {
                std::invoke(element, Args...);
            }
            return;
        }
    }

} // namespace bhe

#endif // BUNNY_HOP_CORE_SRC_BHE_CORE_DELEGATE_HPP
