//
// Created by snizzfox on 7/3/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_RETURN_STATUS_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_RETURN_STATUS_HPP

#include <string>

namespace bhe {
    enum class ReturnStatusCode {
        Unknown = -1,
        Normal = 0,
        NotImplemented,
        Error,
        SingleRunFunctionReran,
        OutOfRange,
    };

    template<typename T, typename Code_T = ReturnStatusCode>
    struct returnStatus {
        T value{true};
        bool exit_normal{true};
        Code_T code{ReturnStatusCode::Normal};
    };


    template<typename Code_T>
    struct returnStatus<void, Code_T> {
        bool exit_normal{true};
        Code_T code{};
    };


    template<>
    struct returnStatus<void, ReturnStatusCode> {
        bool exit_normal{true};
        ReturnStatusCode code{ReturnStatusCode::Normal};
    };

}

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_RETURN_STATUS_HPP
