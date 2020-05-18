//
// Created by snizzfox on 5/16/20.
//

#ifndef MOONLIGHT_TRAILS_DELEGATE_HPP
#define MOONLIGHT_TRAILS_DELEGATE_HPP
#include <vector>
#include <tuple>

inline namespace MT{

    template<class Callable>
    class Delegate{
        std::vector<Callable> callables;
    public:
        Delegate() = default;

        std::vector<Callable> const &operator+=(Callable const & callable);

        template<class ... Args>
        size_t operator()(Args && ... args);

    };

    template<class Callable>
    template<class... Args>
    size_t Delegate<Callable>::operator()(Args &&... args) {
        size_t result{};
        for(auto const & element  : callables){
            element(args ...); ++result;
        }
        return result;
    }

    template<class Callable>
    const std::vector<Callable> &Delegate<Callable>::operator+=(const Callable &callable) {
        callables.emplace_back(callable);
        return callables;
    }

}

#endif //MOONLIGHT_TRAILS_DELEGATE_HPP
