//
// Created by snizzfox on 6/5/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_PIPELINE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_PIPELINE_HPP
#include <functional>
namespace bhe {
    template<class Object_T>
    class pipeline {
    public:
        pipeline() = delete;
        constexpr explicit pipeline(Object_T &Object) : object_{Object} {}
    protected:
        Object_T &object_;
    public:
        template<class Fucntion_T>
        constexpr pipeline& operator|(Fucntion_T function){
            std::invoke(function, object_);
            return *this;
        }

        [[nodiscard]] constexpr auto GetValue() const -> Object_T{return object_;}

    };



} // namespace BHE

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_PIPELINE_HPP
