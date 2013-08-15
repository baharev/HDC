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

	args = {argv, argv+argc};

	add_all_tests();

	run();
}

void test_runner::run() {

	if (args.size() < 2) {

		for (auto&& t : tests) {
			cout << t.first << endl;
		}
	}
	else {

		run_test(args.at(1));
	}
}

void test_runner::run_test(const string& name) {

	cout << "Running test " << name << endl;

	auto test = tests.find(name);

	if (test==tests.end()) {

		cout << "Error: test not found!";
	}
	else {

		test->second->run();
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

	tests.insert(make_move_iterator(begin(test_array)),
			     make_move_iterator(end(test_array)));

}

} // namespace test

} // namespace hdc
