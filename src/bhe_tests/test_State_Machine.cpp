//
// Created by james on 8/11/2020.
//

#include <catch2/catch_test_macros.hpp>

#include <bhe_core/State_Machine.hpp>


TEST_CASE("bhe::State_Machine::Add no args") {

    enum class iterator_type{
        one,
        two,
        three,
    } iteratorType;

    bhe::StateMachine<iterator_type, bool(*)(), 3> stateMachine;

    stateMachine.add(iterator_type::one, []() -> bool { return true; });
    REQUIRE(stateMachine[iterator_type::one]());

    stateMachine.add(iterator_type::two, []() -> bool { return false; });

    REQUIRE(!stateMachine[iterator_type::two]());

    stateMachine.add(iterator_type::three, []() -> bool { return false; });

    REQUIRE(!stateMachine[iterator_type::three]());


}

TEST_CASE("bhe::State_Machine::Add bool arg"){

    enum class iterator_type{
        one,
        two,
        three,
    } iteratorType;

    bhe::StateMachine<iterator_type, bool(*)(bool), 3> stateMachine;

    stateMachine.add(iterator_type::one, [](bool val) -> bool { return val; });
    REQUIRE(stateMachine[iterator_type::one](true));

    stateMachine.add(iterator_type::two, [](bool val) -> bool { return val; });

    REQUIRE(!stateMachine[iterator_type::two](false));

    stateMachine.add(iterator_type::three, [](bool val) -> bool { return val; });

    REQUIRE(!stateMachine[iterator_type::three](false));


}

#include <algorithm>

TEST_CASE("bhe::State_Machine ranged based for loop") {
    enum class iterator_type{
        none = -1,
        one = 1,
        two,
        three,
    } iteratorType;

    bhe::StateMachine<iterator_type, bool(*)(bool)> stateMachine;
    for(auto & [key, value] : stateMachine){
        key = iterator_type::none;
        value = [](bool val){return val;};
    }
    for(auto const & [key, value] : stateMachine){
        REQUIRE(key == iterator_type::none);
    }

    REQUIRE(std::begin(stateMachine) == stateMachine.begin());
    REQUIRE(std::end(stateMachine) == stateMachine.end());

}

TEST_CASE("bhe::State_Machine duplicate elements") {
    enum class iterator_type{
        none = -1,
        one = 1,
        two,
        three,
    } iteratorType;

    bhe::StateMachine<iterator_type, bool(*)(bool)> stateMachine;

    REQUIRE(false);

}
