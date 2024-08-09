//
// Created by snizzfox on 6/1/20.
//


#include "bhe_core/delegate.hpp"

#include <catch2/catch_test_macros.hpp>


TEST_CASE("bhe::delegate += operator") {
    bhe::Delegate<int (*)(int)> del;
    REQUIRE(del.get_size() == 0);
    del += [](int) { return 0; };
    REQUIRE(del.get_size() == 1);
}

TEST_CASE("bhe::delegate inc variable") {
    bhe::Delegate<int (*)(int &)> del;
    del += [](int &val) {
        val = 1;
        return 0;
    };
    int x{0};
    del(x);
    REQUIRE(x == 1);
}

TEST_CASE("bhe::delegate return results") {
    bhe::Delegate<int (*)(int &)> del;
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

