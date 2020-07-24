//
// Created by snizzfox on 7/3/20.
//

#ifndef BUNNY_HOP_CORE_RETURN_STATUS_HPP
#define BUNNY_HOP_CORE_RETURN_STATUS_HPP

#include <string>

namespace bhe {
    template<typename T>
    struct returnStatus {
        T value;
        bool exit_normal;
        std::string message;
    };

    template<>
    struct returnStatus<void> {
        bool exit_normal;
        std::string message;
    };

}

#endif //BUNNY_HOP_CORE_RETURN_STATUS_HPP
