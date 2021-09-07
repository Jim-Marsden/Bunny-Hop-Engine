//
// Created by james on 5/15/2020.
//

#include <limits>
#include "entity.hpp"
#include <iostream>

bhe::Entity::Entity(const sf::Sprite& sprite)
		:Drawable(sprite), speed_{} { }

bhe::Entity::Entity(const sf::Texture& texture)
		:speed_{}
{
	sprite.setTexture(texture);
}

//TODO: Helper functions

bhe::returnStatus<bhe::Entity::collisionDirection>
bhe::Entity::is_colliding(const std::vector<sf::RectangleShape>& rectangles)
{
	collision_direction_.left = collision_direction_.right = collision_direction_.top = collision_direction_
			.bottom = false;
	for (auto const& element : rectangles) {
		if (sprite.getGlobalBounds().intersects(element.getGlobalBounds())) {
			if (is_colliding_top(element).value) {
				//sprite_.setPosition(sprite_.getPosition().x, element.getGlobalBounds().top - sprite_.getOrigin().y);
				auto move_amount_test = ((sprite.getGlobalBounds().height+sprite.getGlobalBounds().top))
						-((element.getGlobalBounds().height+element.getGlobalBounds().top));
				//sprite_.move(0, move_amount_test);//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));

				collision_direction_.top = true;
			}
			if (is_colliding_down(element).value) {
				sprite.move(0, element.getGlobalBounds().top-(sprite.getGlobalBounds().top+sprite.getGlobalBounds()
						.height));//((element.getGlobalBounds().top + element.getGlobalBounds().height)/2) - ((sprite_.getGlobalBounds().top + sprite_.getGlobalBounds().top)/2));
				collision_direction_.bottom = true;
			}
			if (is_colliding_left(element).value) {
				collision_direction_.left = true;
			}
			if (is_colliding_right(element).value) {
				collision_direction_.right = true;
			}
		}
	}
	return {collision_direction_};
}

bhe::returnStatus<bool> bhe::Entity::is_colliding_down(sf::RectangleShape const& Rectangles)
{
	return {true};//{(sprite_.getGlobalBounds().height + sprite_.getGlobalBounds().top) / 2 <= (Rectangles.getGlobalBounds().height + Rectangles.getGlobalBounds().top) /2};

	//return {(sprite_.getGlobalBounds().top < Rectangles.getGlobalBounds().top)};
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
		if (!is_gravity_applied_) {
			//speed_.y += 2;
			is_gravity_applied_ = true;
		}
	}
	else {
		if (is_gravity_applied_) {
			//speed_.y -= 2;
			is_gravity_applied_ = false;
		}
	}
	return {};
}

bhe::returnStatus<decltype(bhe::Entity::health_)> bhe::Entity::get_health() const { return {health_}; }

bhe::returnStatus<void> bhe::Entity::set_health(int health_in)
{
	health_ = health_in;
	return {};
}

bhe::returnStatus<void> bhe::Entity::move(const std::chrono::microseconds& Time)
{
	auto calculate_directions = [](auto const& Speed,
			std::chrono::duration<double, std::milli> const& Time_Local) -> float {
		auto const result = (static_cast<int>( Speed)!=0) ? ((Time_Local.count())/Speed) : 0;
		std::cout << result << '\n';
		return result;
	};

	sprite.move(calculate_directions(movement_.calculate_x(), Time), calculate_directions(movement_.calculate_y(), Time));
	return {};
}

bhe::returnStatus<void> bhe::Entity::move(std::chrono::duration<double> const& time)
{
	auto calculate_directions = [](auto const& speed, std::chrono::duration<double> const& time_local) {
		return (time_local.count()+1)*speed;
	};

	sprite.move(calculate_directions(movement_.calculate_x(), time), calculate_directions(movement_.calculate_y(), time));
	return {};
}

bhe::returnStatus<void> bhe::Entity::add_speed(const sf::Vector2f& speed_in)
{
	speed_ += speed_in;
	return {};
}

bhe::returnStatus<void> bhe::Entity::add_speed_y(float y)
{
	speed_.y += y;
	return {};
}

bhe::returnStatus<void> bhe::Entity::add_speed_x(float x)
{
	speed_.x += x;
	return {};
}

bhe::returnStatus<sf::Vector2f> bhe::Entity::get_speed() const
{
	return {speed_};
}

bhe::returnStatus<void> bhe::Entity::add_movement(std::string const& string_view,
		bhe::Movement::movementDataT const& movement_data)
{
	movement_.add_data(string_view, movement_data);
	return {};
}

bhe::returnStatus<void> bhe::deal_damage(Entity& entity, long damage_amount)
{
	if (auto[health, normal, code] = entity.get_health(); normal) {
		auto amount{health-damage_amount};
		entity.set_health(amount);
		if (entity.get_health().value<1)
			entity.set_health(0);

		return {};
	}
	else {
		return {normal, code};
	}
}

bhe::returnStatus<void> bhe::deal_damage(Entity& entity, long damage_amount,
		std::function<void(Entity&)> const& at_zero)
{
	bhe::deal_damage(entity, damage_amount);
	if (entity.get_health().value<1 && at_zero)
		at_zero(entity);

	return {};
}
