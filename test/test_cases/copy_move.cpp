#include <iostream>
#include <fstream>

#include "json.cpp"
#include "json_correct.cpp"
#include "equal.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest/doctest.h"

TEST_CASE("move assignment 1") {
    try {
        std::string path = "../test_data/redundant.json";
        json a, b, c;
        {
            std::ifstream ifs(path);
            ifs >> a;
        }
        {
            std::ifstream ifs(path);
            ifs >> c;
        }

        b = std::move(a);

        bool equal = (b == c);

        REQUIRE_MESSAGE(
            equal == true,
            "error: move assignment (or loading from file) failed.");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("move assignment 2") {
    try {
        std::string path = "../test_data/redundant.json";
        json a, b;
        {
            std::ifstream ifs(path);
            ifs >> a;
        }
        {
            std::ifstream ifs(path);
            ifs >> b;
        }

        (*(a.begin_list()))["identifiers"] = std::move(b);

        json c = (*(a.begin_list()))["identifiers"];
        std::string str = (*(c.begin_list()))["id"].get_string();

        REQUIRE_MESSAGE(
            str == "AAL",
            "error: move assignment (or loading from file) failed.");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("move constructor") {
    try {
        std::string path = "../test_data/redundant.json";
        json a, c;
        {
            std::ifstream ifs(path);
            ifs >> a;
        }
        {
            std::ifstream ifs(path);
            ifs >> c;
        }

        json b(std::move(a));

        bool equal = (b == c);

        REQUIRE_MESSAGE(
            equal == true,
            "error: move constructor (or loading from file) failed.");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("copy constructor") {
    try {
        std::string path = "../test_data/redundant.json";
        json a, c;
        {
            std::ifstream ifs(path);
            ifs >> a;
        }
        {
            std::ifstream ifs(path);
            ifs >> c;
        }

        json b(a);

        bool equal_ab = (a == b);
        bool equal_bc = (b == c);

        REQUIRE_MESSAGE(
            equal_ab == true,
            "error: copy constructor (or loading from file) failed.");
        REQUIRE_MESSAGE(
            equal_bc == true,
            "error: copy constructor (or loading from file) failed.");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}