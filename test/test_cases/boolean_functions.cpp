#include <iostream>
#include <fstream>

#include "json.cpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest/doctest.h"

TEST_CASE("is_null()") {
    try {
        json j;
        CHECK(j.is_null() == true);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_list()") {
    try {
        json j;
        j.set_list();
        CHECK(j.is_null() == false);
        CHECK(j.is_list() == true);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_dictionary()") {
    try {
        json j;
        j.set_dictionary();
        CHECK(j.is_null() == false);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == true);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_string()") {
    try {
        json j;
        std::string str("hello there!");
        j.set_string(str);
        CHECK(j.is_null() == false);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == true);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_bool()") {
    try {
        json j;
        bool b = false;
        j.set_bool(b);
        CHECK(j.is_null() == false);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == true);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_number()") {
    try {
        json j;
        double d = 3.14;
        j.set_number(d);
        CHECK(j.is_null() == false);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == true);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_null() after set_list() and set_null()") {
    try {
        json j;
        j.set_list();
        j.set_null();
        CHECK(j.is_null() == true);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("is_null() after set_dictionary() and set_null()") {
    try {
        json j;
        j.set_dictionary();
        j.set_null();
        CHECK(j.is_null() == true);
        CHECK(j.is_list() == false);
        CHECK(j.is_dictionary() == false);
        CHECK(j.is_number() == false);
        CHECK(j.is_string() == false);
        CHECK(j.is_bool() == false);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}