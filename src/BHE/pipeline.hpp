//
// Created by snizzfox on 6/5/20.
//

#ifndef BUNNY_HOP_ENGINE_PIPELINE_HPP
#define BUNNY_HOP_ENGINE_PIPELINE_HPP
#include <functional>
namespace bhe {
    template<class Object_T>
    class pipeline {
    public:
        pipeline() = delete;
        constexpr explicit pipeline(Object_T &Object) : object{Object} {}
    protected:
        Object_T &object;
    public:
        constexpr pipeline& operator|(auto function){
            std::invoke(function, object);
            return *this;
        }

        [[nodiscard]] constexpr auto GetValue() const -> Object_T{return object;}

    };



} // namespace BHE

#endif //BUNNY_HOP_ENGINE_PIPELINE_HPP
