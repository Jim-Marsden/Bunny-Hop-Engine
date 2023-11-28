//
// Created by Jim Marsden on 5/15/2020.
//

#include "entity.hpp"
#include <iostream>

bhe::Entity::Entity(const sf::Sprite& sprite)
		:Drawable(sprite), speed{} { }

bhe::Entity::Entity(const sf::Texture& texture)
		:speed{}, Drawable(texture)
{
	sprite.setTexture(texture);
}

//TODO: Helper functions

bhe::returnStatus<bhe::Entity::collisionDirection>
bhe::Entity::is_colliding(const std::vector<sf::RectangleShape>& rectangles)
{
	collision_direction.left = collision_direction.right = collision_direction.top = collision_direction
			.bottom = false;
	for (auto const& element : rectangles) {
		if (sprite.getGlobalBounds().findIntersection(element.getGlobalBounds())){//.intersects(element.getGlobalBounds())) {
			if (is_colliding_top(element).value) {
				//sprite_.setPosition(sprite_.getPosition().x, element.getGlobalBounds().top - sprite_.getOrigin().y);
//				auto move_amount_test = ((sprite.getGlobalBounds().height+sprite.getGlobalBounds().top))
//						-((element.getGlobalBounds().height+element.getGlobalBounds().top));
				//sprite_.move(0, move_amount_test);//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));

				collision_direction.top = true;
			}
//			if (is_colliding_down(element).value) {
//				sprite.move(0, element.getGlobalBounds().top-(sprite.getGlobalBounds().top+sprite.getGlobalBounds()
//						.height));//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));
//				collision_direction.bottom = true;
//			}
//			if (is_colliding_left(element).value) {
//				collision_direction.left = true;
//			}
//			if (is_colliding_right(element).value) {
//				collision_direction.right = true;
//			}
		}
	}
	return {collision_direction};
}

bhe::returnStatus<bool> bhe::Entity::is_colliding_down(sf::RectangleShape const& rectangles)
{
	return {true};//{(sprite_.getGlobalBounds().height + sprite_.getGlobalBounds().top) / 2 <= (rectangles.getGlobalBounds().height + rectangles.getGlobalBounds().top) /2};

	//return {(sprite_.getGlobalBounds().top < rectangles.getGlobalBounds().top)};
}

bhe::returnStatus<bool> bhe::Entity::is_colliding_right(sf::RectangleShape const& rectangles) const
{
	return {(sprite.getGlobalBounds().left<rectangles.getGlobalBounds().left)};
}

bhe::returnStatus<bool> bhe::Entity::is_colliding_left(sf::RectangleShape const& rectangles) const
{
	return {(sprite.getGlobalBounds().left<
			rectangles.getGlobalBounds().left+rectangles.getGlobalBounds().width)};
}

bhe::returnStatus<bool> bhe::Entity::is_colliding_top(const sf::RectangleShape& rectangles) const
{
	return {(sprite.getGlobalBounds().height+sprite.getGlobalBounds().top)/2
					>=(rectangles.getGlobalBounds().height+rectangles.getGlobalBounds().top)/2};

	//return {(sprite_.getGlobalBounds().top <
	//         rectangles.getGlobalBounds().top + rectangles.getGlobalBounds().height)};
}

bhe::returnStatus<void> bhe::Entity::do_gravity(bool doit)
{
	if (doit) {
		if (!is_gravity_applied) {
			//speed.y += 2;
			is_gravity_applied = true;
		}
	}
	else {
		if (is_gravity_applied) {
			//speed.y -= 2;
			is_gravity_applied = false;
		}
	}
	return {};
}

long bhe::Entity::get_health() const { return health; }

void bhe::Entity::set_health(int health_in)
{
	health = health_in;
}

void bhe::Entity::move(std::chrono::microseconds const & speed)
{
	auto calculate_directions = [](auto const& speed,
			std::chrono::duration<double, std::milli> const& time_local) -> float {
		auto const result = (static_cast<int>( speed)!=0) ? ((time_local.count())/speed) : 0;
		std::cout << result << '\n';
		return result;
	};

	sprite.move(
			{calculate_directions(movement.calculate_x(), speed), calculate_directions(movement.calculate_y(), speed)});
}
//
//void bhe::Entity::move(std::chrono::duration<double> const& time)
//{
//	auto calculate_directions = [](auto const& speed, std::chrono::duration<double> const& time_local) -> float{
//		return (time_local.count()+1)*speed;
//	};
//
//	sprite.move(calculate_directions(movement.calculate_x(), time), calculate_directions(movement.calculate_y(), time));
//	return ;
//}
//
void bhe::Entity::add_speed(const sf::Vector2f& speed_in)
{
	speed += speed_in;
}

void bhe::Entity::add_speed_y(float y)
{
	speed.y += y;
}

void bhe::Entity::add_speed_x(float x)
{
	speed.x += x;
}

sf::Vector2f bhe::Entity::get_speed() const
{
	return speed;
}

void bhe::Entity::add_movement(std::string const& string_view,
		bhe::Movement::movementDataT const& movement_data)
{
	movement.add_data(string_view, movement_data);
}

bool bhe::deal_damage(Entity& entity, long damage_amount)
{
	if (auto const & health = entity.get_health(); health > 0) {
		auto amount{health-damage_amount};
		entity.set_health(amount);
		if (entity.get_health()<1)
			entity.set_health(0);

		return true;
	}
	else {
		return false;
	}
}

void bhe::deal_damage(Entity& entity, long damage_amount,
		std::function<void(Entity&)> const& at_zero)
{
	bhe::deal_damage(entity, damage_amount);
	if (entity.get_health()<1 && at_zero)
		at_zero(entity);
}
