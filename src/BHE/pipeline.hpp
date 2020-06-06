//
// Created by snizzfox on 6/5/20.
//

#ifndef BUNNY_HOP_ENGINE_PIPELINE_HPP
#define BUNNY_HOP_ENGINE_PIPELINE_HPP

namespace BHE {
    template<class Object_T>
    class pipeline {
        Object_T &object;
    public:
        pipeline() = delete;

        explicit pipeline(Object_T const &Object) = default;
    };

} // namespace BHE

#endif //BUNNY_HOP_ENGINE_PIPELINE_HPP
