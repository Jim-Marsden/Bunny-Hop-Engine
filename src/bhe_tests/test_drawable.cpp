//
// Created by james on 6/1/2020.
//


#include "bhe_core/drawable.hpp"

#include <catch2/catch.hpp>


TEST_CASE("bhe::drawable default constructor") {
    bhe::Drawable defaultCtr;
    REQUIRE(true);
}


TEST_CASE("bhe::drawable sprite constructor") {
    sf::Sprite sprite;
    bhe::Drawable defaultCtr(sprite);
    REQUIRE(true);
}

TEST_CASE("bhe::drawable::set_position") {
    struct drawableTest : public bhe::Drawable {
        auto get_pos() { return sprite.getPosition(); }
    } drawable_test;

	drawable_test.set_position(2.F, 3.F);
    REQUIRE(static_cast<int>(drawable_test.get_pos().x) == 2);
    REQUIRE(static_cast<int>(drawable_test.get_pos().y) == 3);

}

