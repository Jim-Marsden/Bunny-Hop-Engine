//
// Created by james on 6/1/2020.
//

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS

#include "MT/drawable.hpp"
#include <catch2/catch.hpp>


TEST_CASE("mt::drawable default constructor") {
    mt::drawable defaultCtr;
    REQUIRE(true);
}


TEST_CASE("mt::drawable sprite constructor") {
    sf::Sprite sprite;
    mt::drawable defaultCtr(sprite);
    REQUIRE(true);
}

TEST_CASE("mt::drawable::SetPosition") {
struct drawable_Test : public mt::drawable{

};

    REQUIRE(true);
}



#endif