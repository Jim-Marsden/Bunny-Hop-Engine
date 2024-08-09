//
// Created by snizzfox on 5/16/20.
//

#pragma once

#include <tuple>
#include <vector>
#include <functional>

namespace bhe {

template<class Callable_T>
class Delegate {
	std::vector<Callable_T> callables;

public:
	Delegate() = default;

	std::vector<Callable_T> const& operator+=(Callable_T const& callable);

	template<class... Args_T>
	constexpr auto operator()(Args_T&& ... args) const;

	[[nodiscard]] size_t get_size() const;
};

template<class Callabl_Te>
const std::vector<Callabl_Te>&
Delegate<Callabl_Te>::operator+=(const Callabl_Te& callable)
{
	callables.emplace_back(callable);
	return callables;
}

template<class Callable_T>
size_t Delegate<Callable_T>::get_size() const
{
	return callables.size();
}

template<class Callable_T>
template<class... Args_T>
constexpr auto Delegate<Callable_T>::operator()(Args_T&& ... args) const
{
	if constexpr(!std::is_void<decltype(std::invoke(callables[0], args ...))>::value) {
		using ResultT = decltype(std::invoke(callables[0], args ...));


		if (!callables.empty()) {

			ResultT result;
			bool skip_first = true;

			for (auto const& function : callables) {
				if (skip_first) {
					skip_first = false;
					result = std::invoke(function, args ...);
				}
				std::invoke(function, args ...);
			}
			return result;
		}
		return decltype(std::invoke(callables[0], args ...)){};
	}
	else {
		for (auto const& element : callables) {
			std::invoke(element, args...);
		}
		return;
	}
}

} // namespace bhe
