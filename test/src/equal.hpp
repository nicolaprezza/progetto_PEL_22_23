#include <algorithm>

bool operator==(json_correct const& x, json_correct const& y) {
    if (x.is_bool()) {
        if (not y.is_bool()) return false;
        return x.get_bool() == y.get_bool();
    }

    if (x.is_number()) {
        if (not y.is_number()) return false;
        return x.get_number() == y.get_number();
    }

    if (x.is_null()) return y.is_null();

    if (x.is_string()) {
        if (not y.is_string()) return false;
        return x.get_string() == y.get_string();
    }

    if (x.is_list()) {
        if (not y.is_list()) return false;

        auto it1 = x.begin_list();
        auto it2 = y.begin_list();

        while (it1 != x.end_list() and it2 != y.end_list()) {
            if (not(*it1 == *it2)) return false;
            it1++;
            it2++;
        }

        if ((it1 == x.end_list()) != (it2 == y.end_list())) return false;

        return true;
    }

    if (x.is_dictionary()) {
        if (not y.is_dictionary()) return false;

        auto it1 = x.begin_dictionary();
        auto it2 = y.begin_dictionary();

        int n1 = 0;
        int n2 = 0;

        while (it1 != x.end_dictionary()) {
            it1++;
            n1++;
        }
        while (it2 != y.end_dictionary()) {
            it2++;
            n2++;
        }

        if (n1 != n2) return false;
        if (n1 == n2 and n1 == 0) return true;

        std::pair<std::string, json_correct>* v1 =
            new std::pair<std::string, json_correct>[n1];
        std::pair<std::string, json_correct>* v2 =
            new std::pair<std::string, json_correct>[n2];

        n1 = n2 = 0;

        it1 = x.begin_dictionary();
        it2 = y.begin_dictionary();

        while (it1 != x.end_dictionary()) v1[n1++] = *(it1++);
        while (it2 != y.end_dictionary()) v2[n2++] = *(it2++);

        std::sort(v1, v1 + n1,
                  [](std::pair<std::string, json_correct> x,
                     std::pair<std::string, json_correct> y) {
                      return x.first < y.first;
                  });

        std::sort(v2, v2 + n2,
                  [](std::pair<std::string, json_correct> x,
                     std::pair<std::string, json_correct> y) {
                      return x.first < y.first;
                  });

        bool eq = true;

        for (int i = 0; i < n1; ++i) {
            if ((v1[i].first != v2[i].first) or
                (not(v1[i].second == v2[i].second)))
                eq = false;
        }

        delete[] v1;
        delete[] v2;

        return eq;
    }

    return false;
}

bool operator==(json const& x, json const& y) {
    if (x.is_bool()) {
        if (not y.is_bool()) return false;
        return x.get_bool() == y.get_bool();
    }

    if (x.is_number()) {
        if (not y.is_number()) return false;
        return x.get_number() == y.get_number();
    }

    if (x.is_null()) return y.is_null();

    if (x.is_string()) {
        if (not y.is_string()) return false;
        return x.get_string() == y.get_string();
    }

    if (x.is_list()) {
        if (not y.is_list()) return false;

        auto it1 = x.begin_list();
        auto it2 = y.begin_list();

        while (it1 != x.end_list() and it2 != y.end_list()) {
            if (not(*it1 == *it2)) return false;
            it1++;
            it2++;
        }

        if ((it1 == x.end_list()) != (it2 == y.end_list())) return false;

        return true;
    }

    if (x.is_dictionary()) {
        if (not y.is_dictionary()) return false;

        auto it1 = x.begin_dictionary();
        auto it2 = y.begin_dictionary();

        int n1 = 0;
        int n2 = 0;

        while (it1 != x.end_dictionary()) {
            it1++;
            n1++;
        }
        while (it2 != y.end_dictionary()) {
            it2++;
            n2++;
        }

        if (n1 != n2) return false;
        if (n1 == n2 and n1 == 0) return true;

        std::pair<std::string, json>* v1 = new std::pair<std::string, json>[n1];
        std::pair<std::string, json>* v2 = new std::pair<std::string, json>[n2];

        n1 = n2 = 0;

        it1 = x.begin_dictionary();
        it2 = y.begin_dictionary();

        while (it1 != x.end_dictionary()) v1[n1++] = *(it1++);
        while (it2 != y.end_dictionary()) v2[n2++] = *(it2++);

        std::sort(
            v1, v1 + n1,
            [](std::pair<std::string, json> x, std::pair<std::string, json> y) {
                return x.first < y.first;
            });

        std::sort(
            v2, v2 + n2,
            [](std::pair<std::string, json> x, std::pair<std::string, json> y) {
                return x.first < y.first;
            });

        bool eq = true;

        for (int i = 0; i < n1; ++i) {
            if ((v1[i].first != v2[i].first) or
                (not(v1[i].second == v2[i].second)))
                eq = false;
        }

        delete[] v1;
        delete[] v2;

        return eq;
    }

    return false;
}

bool operator==(json const& x, json_correct const& y) {
    if (x.is_bool()) {
        if (not y.is_bool()) return false;
        return x.get_bool() == y.get_bool();
    }

    if (x.is_number()) {
        if (not y.is_number()) return false;
        return x.get_number() == y.get_number();
    }

    if (x.is_null()) return y.is_null();

    if (x.is_string()) {
        if (not y.is_string()) return false;
        return x.get_string() == y.get_string();
    }

    if (x.is_list()) {
        if (not y.is_list()) return false;

        auto it1 = x.begin_list();
        auto it2 = y.begin_list();

        while (it1 != x.end_list() and it2 != y.end_list()) {
            if (not(*it1 == *it2)) return false;
            it1++;
            it2++;
        }

        if ((it1 == x.end_list()) != (it2 == y.end_list())) return false;

        return true;
    }

    if (x.is_dictionary()) {
        if (not y.is_dictionary()) return false;

        auto it1 = x.begin_dictionary();
        auto it2 = y.begin_dictionary();

        int n1 = 0;
        int n2 = 0;

        while (it1 != x.end_dictionary()) {
            it1++;
            n1++;
        }
        while (it2 != y.end_dictionary()) {
            it2++;
            n2++;
        }

        if (n1 != n2) return false;
        if (n1 == n2 and n1 == 0) return true;

        std::pair<std::string, json>* v1 = new std::pair<std::string, json>[n1];
        std::pair<std::string, json_correct>* v2 =
            new std::pair<std::string, json_correct>[n2];

        n1 = n2 = 0;

        it1 = x.begin_dictionary();
        it2 = y.begin_dictionary();

        while (it1 != x.end_dictionary()) v1[n1++] = *(it1++);
        while (it2 != y.end_dictionary()) v2[n2++] = *(it2++);

        std::sort(
            v1, v1 + n1,
            [](std::pair<std::string, json> x, std::pair<std::string, json> y) {
                return x.first < y.first;
            });

        std::sort(v2, v2 + n2,
                  [](std::pair<std::string, json_correct> x,
                     std::pair<std::string, json_correct> y) {
                      return x.first < y.first;
                  });

        bool eq = true;

        for (int i = 0; i < n1; ++i) {
            if ((v1[i].first != v2[i].first) or
                (not(v1[i].second == v2[i].second)))
                eq = false;
        }

        delete[] v1;
        delete[] v2;

        return eq;
    }

    return false;
}

bool operator==(json_correct const& x, json const& y) { return y == x; }