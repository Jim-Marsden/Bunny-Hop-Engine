//
// Created by snizzfox on 6/1/20.
//

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS

#include "BHE/delegate.hpp"
#include <catch2/catch.hpp>


TEST_CASE("mt::delegate += operator") {
    mt::delegate<int(*)(int)> del;
    REQUIRE(del.GetSize() == 0);
    del += [](int){return 0;};
    REQUIRE(del.GetSize() == 1);
}


#endif