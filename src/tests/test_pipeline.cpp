//
// Created by snizzfos on 6/5/20.
//

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS

#include "pipeline.hpp"
#include <catch2/catch.hpp>
TEST_CASE("bhe::pipeline accumilate") {
    int x{};
    bhe::pipeline<int> pl(x);

    pl | [](int & x){ x += 1;};
    REQUIRE(pl.GetValue() == 1);

    pl | [](int & x){ x += 1;};
    REQUIRE(pl.GetValue() == 2);
}



TEST_CASE("bhe::pipeline muliple functions") {
    int x{};
    bhe::pipeline<int> pl(x);

    pl | [](int & x){ x += 2;} | [](int & x){ --x;};
    REQUIRE(pl.GetValue() == 1);

}

#endif