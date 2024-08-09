//
// Created by Jim Marsden on 6/5/20.
//

#pragma once
#include <functional>
namespace bhe {
template<class Object_T>
class Pipeline {
public:
	Pipeline() = delete;
	constexpr explicit Pipeline(Object_T& object)
			:object{object} { }
protected:
	Object_T& object;
public:
	template<class Fucntion_T>
	constexpr Pipeline& operator|(Fucntion_T function)
	{
		std::invoke(function, object);
		return *this;
	}

	[[nodiscard]] constexpr auto get_value() const -> Object_T { return object; }

};

} // namespace BHE
