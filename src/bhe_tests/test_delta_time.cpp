//
// Created by Jim on 12/7/23.
//

#include "../bhe_core/delta_time.hpp"
#include <catch2/catch_test_macros.hpp>
#include <type_traits>

#include "catch2/matchers/catch_matchers_vector.hpp"


TEST_CASE("bhe::delta_time::construction []")
{
    CHECK(std::is_default_constructible_v<bhe::delta_time>);
    CHECK(std::is_copy_assignable_v<bhe::delta_time>);
    CHECK(std::is_assignable_v<bhe::delta_time, bhe::delta_time>);
    CHECK(std::is_constructible_v<bhe::delta_time, bhe::delta_time::time_point>);
    CHECK(std::is_move_assignable_v<bhe::delta_time>);
    CHECK(std::is_trivially_assignable_v<bhe::delta_time, bhe::delta_time>);

    auto pt = bhe::delta_time::clock::now();
    bhe::delta_time dt;
    CHECK(dt.get_first_time_point() < bhe::delta_time::clock::now());
    CHECK(dt.get_first_time_point() == dt.get_second_time_point());
    CHECK(dt.get_first_time_point() > pt);
}

TEST_CASE("bhe::delta_time::shift")
{
    bhe::delta_time dt;
    CHECK(dt.get_first_time_point() == dt.get_second_time_point());
    auto old_first = dt.get_first_time_point();
    dt.shift();
    CHECK(old_first == dt.get_second_time_point());
    CHECK(dt.get_first_time_point() > dt.get_second_time_point());
    auto new_time = bhe::delta_time::clock::now();
    old_first = dt.get_first_time_point();

    dt.shift(new_time);
    CHECK(old_first == dt.get_second_time_point());
    CHECK(dt.get_first_time_point() > dt.get_second_time_point());
}

TEST_CASE("bhe::delta_time::delta")
{
    using duration = bhe::delta_time::duration;
    bhe::delta_time dt;
    CHECK(dt.delta().count() == 0);

    auto const old_first_time = dt.get_first_time_point();
    dt.shift(old_first_time + std::chrono::minutes(1));
    CHECK(dt.delta().count() == Catch::Approx(60));

}