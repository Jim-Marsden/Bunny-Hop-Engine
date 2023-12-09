//
// Created by Jim Marsden on 7/3/20.
//

#pragma once

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
