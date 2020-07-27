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

TEST_CASE("bhe::delegate inc variable") {
    bhe::delegate<int (*)(int &)> del;
    del += [](int &val) {
        val = 1;
        return 0;
    };
    int x{0};
    del(x);
    REQUIRE(x == 1);
}

TEST_CASE("bhe::delegate return results") {
    bhe::delegate<int (*)(int &)> del;
    del += [](int &val) {
        val = 1;
        return 0;
    };
    del += [](int &val) {
        val = 1;
        return 1;
    };
    del += [](int &val) {
        val = 1;
        return 2;
    };

    int x{0};
    del(x);
    REQUIRE(del(x) == 0);
}

