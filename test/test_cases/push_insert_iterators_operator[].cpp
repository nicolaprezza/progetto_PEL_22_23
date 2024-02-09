#include <iostream>
#include <fstream>

#include "json.cpp"
#include "json_correct.cpp"
#include "equal.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "external/doctest/doctest/doctest.h"

TEST_CASE("push_front() + access list with iterators") {
    try {
        json j1;
        j1.set_list();

        json j2;
        j2.set_list();

        json j3;
        j3.set_number(-3.14);

        json j4;
        j4.set_number(12345);

        json j5;
        j5.set_bool(false);

        json j6;

        json j7;
        std::string s{"test"};
        j7.set_string(s);

        j1.push_front(j2);
        j1.push_front(j3);
        j1.push_front(j4);
        j1.push_front(j5);
        j1.push_front(j6);
        j1.push_front(j7);

        //"test"  ->  null  ->  false  ->  12345  ->  -3.14 ->  []

        auto it = j1.begin_list();

        CHECK((it++)->is_string() == true);
        CHECK((it++)->is_null() == true);
        CHECK((it++)->is_bool() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it)->is_list() == true);

        CHECK(it->begin_list() == it->end_list());
        ++it;

        CHECK(it == j1.end_list());
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("push_back() + access list with iterators") {
    try {
        json j1;
        j1.set_list();

        json j2;
        j2.set_list();

        json j3;
        j3.set_number(-3.14);

        json j4;
        j4.set_number(12345);

        json j5;
        j5.set_bool(false);

        json j6;

        json j7;
        std::string s{"test"};
        j7.set_string(s);

        j1.push_back(j7);
        j1.push_back(j6);
        j1.push_back(j5);
        j1.push_back(j4);
        j1.push_back(j3);
        j1.push_back(j2);

        auto it = j1.begin_list();

        CHECK((it++)->is_string() == true);
        CHECK((it++)->is_null() == true);
        CHECK((it++)->is_bool() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it)->is_list() == true);

        CHECK(it->begin_list() == it->end_list());
        ++it;

        CHECK(it == j1.end_list());
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("access list with const_iterator") {
    try {
        json j1;
        j1.set_list();

        json j2;
        j2.set_list();

        json j3;
        j3.set_number(-3.14);

        json j4;
        j4.set_number(12345);

        json j5;
        j5.set_bool(false);

        json j6;

        json j7;
        std::string s{"test"};
        j7.set_string(s);

        j1.push_back(j7);
        j1.push_back(j6);
        j1.push_back(j5);
        j1.push_back(j4);
        j1.push_back(j3);
        j1.push_back(j2);

        json const& j8 = j1;

        json::const_list_iterator it = j8.begin_list();

        CHECK((it++)->is_string() == true);
        CHECK((it++)->is_null() == true);
        CHECK((it++)->is_bool() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it++)->is_number() == true);
        CHECK((it)->is_list() == true);

        CHECK(it->begin_list() == it->end_list());
        ++it;

        bool res = (it == j8.end_list());
        CHECK(res == true);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("insert() + access dictionary with iterators + copy assignment") {
    try {
        json j1;
        j1.set_dictionary();

        json j2;
        j2.set_list();

        json j3;
        j3.set_number(-3.14);

        json j4;
        j4.set_number(12345);

        json j5;
        j5.set_bool(false);

        json j6;

        json j7;
        std::string s{"test"};
        j7.set_string(s);

        std::pair<std::string, json> p2{"j2", j2};
        std::pair<std::string, json> p3{"j3", j3};
        std::pair<std::string, json> p4{"j4", j4};
        std::pair<std::string, json> p5{"j5", j5};
        std::pair<std::string, json> p6{"j6", j6};
        std::pair<std::string, json> p7{"j7", j7};

        j1.insert(p2);
        j1.insert(p3);
        j1.insert(p4);
        j1.insert(p5);
        j1.insert(p6);
        j1.insert(p7);

        std::pair<std::string, json> v1[] = {p2, p3, p4, p5, p6, p7};
        std::pair<std::string, json> v2[6];

        auto it = j1.begin_dictionary();
        int i = 0;

        while (i < 6 && it != j1.end_dictionary()) v2[i++] = *(it++);

        bool cond = (i == 6) and (it == j1.end_dictionary());

        REQUIRE_MESSAGE(cond == true,
                        "error: number of inserted and extracted elements from "
                        "dictionary differ.");

        std::sort(
            v1, v1 + 6,
            [](std::pair<std::string, json> x, std::pair<std::string, json> y) {
                return x.first < y.first;
            });

        std::sort(
            v2, v2 + 6,
            [](std::pair<std::string, json> x, std::pair<std::string, json> y) {
                return x.first < y.first;
            });

        bool set_inserts_succeeded = true;

        for (int i = 0; i < 6; ++i) set_inserts_succeeded &= (v1[i] == v2[i]);

        REQUIRE_MESSAGE(
            set_inserts_succeeded == true,
            "error: inserted and extracted elements in dictionary differ.");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("list push_back and push_front") {
    try {
        json A;
        A.set_list();

        json B;
        B.set_list();

        json j2;
        j2.set_list();

        json j3;
        j3.set_number(-3.14);

        json j4;
        j4.set_number(12345);

        json j5;
        j5.set_bool(false);

        json j6;

        json j7;
        std::string s{"test"};
        j7.set_string(s);

        A.push_back(j2);
        A.push_back(j3);
        A.push_back(j4);
        A.push_front(j5);
        A.push_front(j6);
        A.push_front(j7);

        // j7 j6 j5 j2 j3 j4

        B.push_front(j6);
        B.push_back(j5);
        B.push_front(j7);
        B.push_back(j2);
        B.push_back(j3);
        B.push_back(j4);

        // j7 j6 j5 j2 j3 j4

        REQUIRE_MESSAGE(
            A == B,
            "error: two json of type list should be equal but are different");

        A.set_list();
        B.set_list();

        REQUIRE_MESSAGE(
            A == B,
            "error: two json of type list should be equal but are different");

        A.set_dictionary();
        B.set_dictionary();

        REQUIRE_MESSAGE(
            A == B,
            "error: two json of type dictionary should be equal but "
            "are different");
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE(
    "access with iterators and operator[] and modifications with copy "
    "assignment") {
    try {
        json j3;
        j3.set_number(-56);
        // j3 = -56

        json j4;
        j4.set_dictionary();
        j4["a1"] = {};
        j4["a2"] = {};
        // j4 = {"a1":null, "a2":null}

        CHECK(j4["a1"].is_null() == true);

        json j2;
        j2.set_dictionary();
        j2["k1"] = {};
        j2["k2"] = {};
        j2["k2"].set_list();
        j2["k2"].push_back({});
        j2["k2"].push_back(j3);
        j2["k3"] = j4;

        auto it2 = j2["k2"].begin_list();
        CHECK((*(++it2)).get_number() == -56);

        /*
        j2 =
        {
          "k1" : null,
          "k2" : [null,-56],
          "k3" : {"a1":null, "a2":null}
        }
        */

        json j1;
        j1.set_list();
        j1.push_back({});
        j1.push_back(j2);

        /*
        j1 =

          [
            null,
            {
              "k1" : null,
              "k2" : [null,-56],
              "k3" : {"a1":null, "a2":null}
            }
          ]

        */

        auto it1 = j1.begin_list();
        it1++;

        CHECK((*it1)["k3"]["a2"].is_null() == true);

        ++it1;

        CHECK(it1 == j1.end_list());
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}

TEST_CASE("operator[] on nonexisting key") {
    try {
        json j;
        j.set_dictionary();

        CHECK(j["nonexisting"].is_null() == true);
    } catch (json_exception e) {
        REQUIRE_MESSAGE(false,
                        "ERROR unexpected json_exception thrown: " << e.msg);
    }
}