//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#ifndef TEST_BASE_HPP_
#define TEST_BASE_HPP_

namespace hdc {

namespace test {

class test_base {

public:

	virtual void run() = 0;

	virtual ~test_base() { }

private:

};

}

}

#endif
