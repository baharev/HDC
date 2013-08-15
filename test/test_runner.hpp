//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//

#ifndef TEST_RUNNER_HPP_
#define TEST_RUNNER_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>


namespace hdc {

namespace test {

class test_base;

class test_runner {

public:

    test_runner(int argc, char* argv[]);

    ~test_runner();

private:

    void add_all_tests();

    void run();

    void run_test(const std::string& name);

    std::vector<std::string> args;

    std::map<std::string,std::unique_ptr<test_base>> tests;

};

}

}

#endif
