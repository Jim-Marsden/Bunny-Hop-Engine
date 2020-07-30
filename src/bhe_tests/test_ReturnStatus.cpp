//
// Created by snizzfox on 7/29/20.
//

#include <bhe_core/Return_Status.hpp>

#include <catch2/catch.hpp>


TEST_CASE("bhe::returnStatus void") {

    {
        auto lambdaTest = []() -> bhe::returnStatus<void> { return {}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code == bhe::ReturnStatusCode::Normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<void> { return {false}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(!valid);
        REQUIRE(code == bhe::ReturnStatusCode::Normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<void> { return {true, bhe::ReturnStatusCode::Error}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code != bhe::ReturnStatusCode::Normal);
    }
}

TEST_CASE("bhe::returnStatus void custom enum") {
    enum class localEnumTest {
        normal = 0,
        error,
    };

    {
        auto lambdaTest = []() -> bhe::returnStatus<void, localEnumTest> { return {}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code == localEnumTest::normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<void, localEnumTest> { return {false}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(!valid);
        REQUIRE(code == localEnumTest::normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<void, localEnumTest> { return {true, localEnumTest::error}; };
        auto [valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code != localEnumTest::normal);
    }
}


TEST_CASE("bhe::returnStatus value") {

    {
        auto lambdaTest = []() -> bhe::returnStatus<int> { return {}; };
        auto [value, valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code == bhe::ReturnStatusCode::Normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<int> { return {0, false}; };

        auto [value, valid, code] = lambdaTest();

        REQUIRE(!valid);
        REQUIRE(code == bhe::ReturnStatusCode::Normal);
    }
    {
        auto lambdaTest = []() -> bhe::returnStatus<int> { return {0, true, bhe::ReturnStatusCode::Error}; };
        auto [value, valid, code] = lambdaTest();

        REQUIRE(valid);
        REQUIRE(code != bhe::ReturnStatusCode::Normal);
    }
}
