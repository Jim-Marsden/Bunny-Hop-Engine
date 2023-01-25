//
// Created by snizzfox on 8/1/20.
//

#include <catch2/catch_test_macros.hpp>
#include <bhe_core/entity.hpp>
#include <algorithm>
#include <memory>

constexpr auto TestTextureFilepath{".Test/images/test.png"};

TEST_CASE("bhe::entity constructors"){


  auto texture = std::make_unique<sf::Texture>();
  REQUIRE(texture->loadFromFile(TestTextureFilepath));

  sf::Sprite sprite(*texture);
  bhe::Entity entity_1(sprite);

  auto ctr_copy = [](bhe::Entity e){return true;};
  auto ctr_move = [](bhe::Entity && e){return true;};
  auto ctr_sprite = [sprite](){bhe::Entity entity_local(sprite); return true;};
  auto ctr_texture = [&texture](){bhe::Entity entity_local(*texture); return true;};

  REQUIRE(ctr_copy(entity_1));
  REQUIRE(ctr_sprite());
  REQUIRE(ctr_texture());
  REQUIRE(ctr_move(std::move(entity_1)));
}

TEST_CASE("bhe::entity::is_colliding"){
  auto texture = std::make_unique<sf::Texture>();


  REQUIRE(texture->loadFromFile(TestTextureFilepath));
  sf::Sprite sprite(*texture);

  bhe::Entity herp_derp(sprite);

  std::vector<sf::RectangleShape> shapes;
  shapes.emplace_back(sf::RectangleShape(sf::Vector2f(64, 64)));

  auto collision_directions_result = herp_derp.is_colliding(shapes);
  REQUIRE(collision_directions_result.exit_normal);
  REQUIRE(collision_directions_result.value.top);
  REQUIRE(collision_directions_result.value.bottom);
  REQUIRE(collision_directions_result.value.left);
  REQUIRE(collision_directions_result.value.right);

/*
  shapes.back().move(60, 60);

  collision_directions_result = herp_derp.IsColliding(shapes);
  REQUIRE(collision_directions_result.exit_normal);
  REQUIRE(collision_directions_result.value.bottom);
  REQUIRE(collision_directions_result.value.top);
  REQUIRE(collision_directions_result.value.left);
  REQUIRE(collision_directions_result.value.right);
  shapes.back().move(0, -60);

  collision_directions_result = herp_derp.is_colliding(shapes);
  REQUIRE(collision_directions_result.exit_normal);
  REQUIRE(collision_directions_result.value.bottom);
  REQUIRE(collision_directions_result.value.top);
  REQUIRE(collision_directions_result.value.left);
  REQUIRE(collision_directions_result.value.right);
  */


}