//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//

#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include "test_runner.hpp"
#include "all_classes_include.hpp"

using namespace std;

namespace hdc {

namespace test {

test_runner::~test_runner() {
    // out of line dtor due to incomplete type test_base
}

test_runner::test_runner(int argc, char* argv[]) {

    args = {argv+1, argv+argc};

    add_all_tests();

    run();
}

void test_runner::run() {

    if (!args.empty()) {

        run_test(args.at(0));
    }
    else {

        for (auto&& t : tests) {
            cout << t.first << endl;
        }
    }
}

void test_runner::run_test(const string& name) {

    cout << "Running test " << name << endl;

    auto test = tests.find(name);

    if (test!=tests.end()) {

        test->second->run();
    }
    else {

        cout << "Error: test not found!";
    }
}

//------------------------------------------------------------------------------

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T> (new T(std::forward<Args>(args)...));
}

void test_runner::add_all_tests() {

    pair<string,unique_ptr<test_base>> test_array[] = {
#include "test_classes"
    };

    move(begin(test_array), end(test_array), inserter(tests, tests.end()));
}

} // namespace test

} // namespace hdc
