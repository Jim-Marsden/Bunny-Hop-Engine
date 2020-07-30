//
// Created by snizzfox on 7/29/20.
//

#include <bhe_core/Return_Status.hpp>

#include <catch2/catch.hpp>


TEST_CASE("bhe::returnStatus void") {

    {
        auto lambda_test = []() -> bhe::returnStatus<void> { return {}; };
        auto [valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code == bhe::returnStatusCode::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<void> { return {false}; };
        auto [valid, code] = lambda_test();

        REQUIRE(!valid);
        REQUIRE(code == bhe::returnStatusCode::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<void> { return {true, bhe::returnStatusCode::Error}; };
        auto [valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code != bhe::returnStatusCode::Normal);
    }
}

TEST_CASE("bhe::returnStatus void custom enum") {
    enum class local_enum_test{
        Normal = 0,
        Error,
    };

    {
        auto lambda_test = []() -> bhe::returnStatus<void, local_enum_test> { return {}; };
        auto [valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code == local_enum_test::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<void, local_enum_test> { return {false}; };
        auto [valid, code] = lambda_test();

        REQUIRE(!valid);
        REQUIRE(code == local_enum_test::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<void, local_enum_test> { return {true, local_enum_test::Error}; };
        auto [valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code != local_enum_test::Normal);
    }
}


TEST_CASE("bhe::returnStatus value") {

    {
        auto lambda_test = []() -> bhe::returnStatus<int> { return {}; };
        auto [value, valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code == bhe::returnStatusCode::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<int> { return {0, false}; };

        //        auto lambda_test = []() -> bhe::returnStatus<void> { return {false}; };
        auto [value, valid, code] = lambda_test();

        REQUIRE(!valid);
        REQUIRE(code == bhe::returnStatusCode::Normal);
    }
    {
        auto lambda_test = []() -> bhe::returnStatus<int> { return {0, true, bhe::returnStatusCode::Error}; };
        auto [value, valid, code] = lambda_test();

        REQUIRE(valid);
        REQUIRE(code != bhe::returnStatusCode::Normal);
    }
}
