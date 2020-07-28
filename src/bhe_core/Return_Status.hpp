//
// Created by snizzfox on 7/3/20.
//

#ifndef BUNNY_HOP_CORE_RETURN_STATUS_HPP
#define BUNNY_HOP_CORE_RETURN_STATUS_HPP

#include <string>

namespace bhe {
    enum class returnStatusCode {
        Unknown = -1,
        Normal = 0,
        NotImplemented,
        Error,
        SingleRunFunctionReran,
        OutOfRange,
    };

    template<typename T, typename Code_T = returnStatusCode>
    struct returnStatus {
        T value{true};
        bool exit_normal{true};
        Code_T code{returnStatusCode::Normal};
    };


    template<typename Code_T>
    struct returnStatus<void, Code_T> {
        bool exit_normal{true};
        Code_T code{};
    };


    template<>
    struct returnStatus<void, returnStatusCode> {
        bool exit_normal{true};
        returnStatusCode code{returnStatusCode::Normal};
    };

}

#endif //BUNNY_HOP_CORE_RETURN_STATUS_HPP
