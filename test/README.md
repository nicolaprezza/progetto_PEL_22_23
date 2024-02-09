Tests for PEL project a.y. 22-23
--------------------------------

#### Dependencies

It is necessary to do

    git submodule update --init --recursive

before compiling a test to pull the `external/doctest` dependency.

#### Test data

The tests use the json files contained in the folder `test_data`.

#### Compiling and running a test

**Important note:** It is assumed that the `src` folder contains a file `json.cpp` with **your** implementation
and a reference `json_correct.cpp` implementation to compare against (which implements the same interface defined in `json.hpp` but under the name `json_correct.hpp`.)

From within the `test_cases` folder,
compile a test with

    g++ -g -std=c++17 -I ../src -I ../ [test-name].cpp -o test-name

where `[test-name]` is the name of the test. For example:

    g++ -g -std=c++17 -I ../src -I ../ copy_move.cpp -o copy_move

and run it with `./copy_move` and then with `valgrind ./copy_move`.