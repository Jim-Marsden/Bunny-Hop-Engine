//
// Created by snizzfos on 6/5/20.
//



#include "bhe_core/Pipeline.hpp"


#include <catch2/catch.hpp>

TEST_CASE("bhe::pipeline accumilate") {
    int x{};
    bhe::Pipeline<int> pl(x);

    pl | [](int &x) { x += 1; };
    REQUIRE(pl.get_value() == 1);

    pl | [](int &x) { x += 1; };
    REQUIRE(pl.get_value() == 2);
}



TEST_CASE("bhe::pipeline muliple functions") {
    int x{};
    bhe::Pipeline<int> pl(x);

    pl | [](int & x){ x += 2;} | [](int & x){ --x;};
    REQUIRE(pl.get_value() == 1);

}

