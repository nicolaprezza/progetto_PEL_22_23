#include <iostream>
#include <fstream>

#include "json.cpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest/doctest.h"

TEST_CASE("set_string() and get_string()") {
    try {
        json j;
        std::string str("hello there!");
        j.set_string(str);
        REQUIRE_MESSAGE(j.get_string() == str,
                        "error: expected string '" << str << "'");

        std::string str2("bye bye");
        j.get_string() = str2;
        REQUIRE_MESSAGE(j.get_string() == str2,
                        "error: expected string '" << str2 << "'");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("set_bool() and get_bool()") {
    try {
        json j;
        bool b1 = false;
        j.set_bool(b1);
        REQUIRE_MESSAGE(j.get_bool() == b1,
                        "error: expected bool '" << false << "'");

        j.get_bool() = true;

        REQUIRE_MESSAGE(j.get_bool() == true,
                        "error: expected bool '" << true << "'");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("set_number() and get_number()") {
    try {
        json j;
        double d1 = -3.14;
        j.set_number(d1);
        REQUIRE_MESSAGE(j.get_number() == d1,
                        "error: expected number '" << d1 << "'");

        j.get_number() = 102.234;

        REQUIRE_MESSAGE(j.get_number() == 102.234,
                        "error: expected number '" << 102.234 << "'");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}