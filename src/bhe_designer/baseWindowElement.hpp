//
// Created by snizzfox on 7/4/20.
//

#ifndef BUNNY_HOP_CORE_BASEWINDOWELEMENT_HPP
#define BUNNY_HOP_CORE_BASEWINDOWELEMENT_HPP

#include <bhe_core/Return_Status.hpp>

class baseWindowElement {
public:
    virtual bhe::returnStatus<void> InitWindow();

    virtual auto Close() -> bhe::returnStatus<void>;

    baseWindowElement() = default;

    virtual ~baseWindowElement() = default;

    baseWindowElement(baseWindowElement const &) = default;

    baseWindowElement(baseWindowElement &&) = default;

    baseWindowElement &operator=(baseWindowElement const &) = default;

    baseWindowElement &operator=(baseWindowElement &&) = default;


};


#endif //BUNNY_HOP_CORE_BASEWINDOWELEMENT_HPP
