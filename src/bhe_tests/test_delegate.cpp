//
// Created by snizzfox on 6/1/20.
//


#include "bhe_core/delegate.hpp"

#include <catch2/catch.hpp>


TEST_CASE("bhe::delegate += operator") {
    bhe::delegate<int (*)(int)> del;
    REQUIRE(del.GetSize() == 0);
    del += [](int) { return 0; };
    REQUIRE(del.GetSize() == 1);
}

