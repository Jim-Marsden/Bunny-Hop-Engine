//
// Created by james on 6/1/2020.
//


#include "../bhe_core/drawable.hpp"

#include <catch2/catch_test_macros.hpp>




TEST_CASE("bhe::drawable sprite constructor") {
    sf::Texture empty_texture;
    sf::Sprite sprite{empty_texture};
    bhe::Drawable defaultCtr(sprite);
    REQUIRE(true);
}

TEST_CASE("bhe::drawable::set_position") {
    sf::Texture empty_texture;
    struct drawableTest : public bhe::Drawable {
        auto get_pos() { return sprite.getPosition(); }
        explicit drawableTest(sf::Texture const &texture) : Drawable(texture){}
    } drawable_test{empty_texture};

	drawable_test.set_position(2.F, 3.F);
    REQUIRE(static_cast<int>(drawable_test.get_pos().x) == 2);
    REQUIRE(static_cast<int>(drawable_test.get_pos().y) == 3);

}

