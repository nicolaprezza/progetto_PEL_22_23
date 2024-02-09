#include <iostream>
#include <fstream>

#include "json.cpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest/doctest.h"

TEST_CASE("tests on exceptions - 1") {
    json j;
    j.set_list();

    bool exception_thrown = false;

    try {
        auto it = j.begin_dictionary();
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(
        exception_thrown == true,
        "error: begin_dictionary() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 2") {
    json j;

    bool exception_thrown = false;

    try {
        auto it = j.begin_dictionary();
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(
        exception_thrown == true,
        "error: begin_dictionary() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 3") {
    json j;
    j.set_number(3);

    bool exception_thrown = false;

    try {
        auto it = j.begin_list();
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(exception_thrown == true,
                    "error: begin_list() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 4") {
    json j;
    j.set_list();

    bool exception_thrown = false;

    try {
        auto x = j.get_number();
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(exception_thrown == true,
                    "error: get_number() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 5") {
    json j;
    j.set_list();

    bool exception_thrown = false;

    try {
        std::pair<std::string, json> p;
        j.insert(p);
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(exception_thrown == true,
                    "error: insert() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 6") {
    json j;
    j.set_dictionary();

    bool exception_thrown = false;

    try {
        json x;
        j.push_back(x);
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(exception_thrown == true,
                    "error: push_back() did not throw the expected exception");
}

TEST_CASE("tests on exceptions - 7") {
    json j;
    std::string s;
    j.set_string(s);

    bool exception_thrown = false;

    try {
        json x;
        j.push_back(x);
    } catch (json_exception e) { exception_thrown = true; }

    REQUIRE_MESSAGE(exception_thrown == true,
                    "error: push_back() did not throw the expected exception");
}