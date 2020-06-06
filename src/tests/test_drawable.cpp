//
// Created by james on 6/1/2020.
//

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS

#include "BHE/drawable.hpp"
#include <catch2/catch.hpp>


TEST_CASE("bhe::drawable default constructor") {
    bhe::drawable defaultCtr;
    REQUIRE(true);
}


TEST_CASE("bhe::drawable sprite constructor") {
    sf::Sprite sprite;
    bhe::drawable defaultCtr(sprite);
    REQUIRE(true);
}

TEST_CASE("bhe::drawable::SetPosition") {
    struct drawableTest : public bhe::drawable {
        auto get_pos() { return _sprite.getPosition(); }
    } drawable_test;


    drawable_test.SetPosition(2.F, 3.F);


    REQUIRE(static_cast<int>(drawable_test.get_pos().x) == 2);
    REQUIRE(static_cast<int>(drawable_test.get_pos().y) == 3);

}






#endif