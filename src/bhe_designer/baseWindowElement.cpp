//
// Created by snizzfox on 7/4/20.
//

#include "baseWindowElement.hpp"

bhe::returnStatus<void> baseWindowElement::InitWindow() {
    return bhe::returnStatus<void>{false, "Not implemented"};
}

auto baseWindowElement::Close() -> bhe::returnStatus<void> {
    return bhe::returnStatus<void>{false, "Not implemented"};
}
