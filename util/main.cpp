//  Copyright (C) Ali Baharev, 2013
//  All rights reserved.
//
//  Please refer to the LICENSE file in the top directory
//
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

const string excluded[] = { "all_classes_include", "test_base", "test_runner"};

const string name_includes(excluded[0]+".hpp");

const string name_classes("test_classes");

//-----------------------------------------------------------------------------

bool is_excluded(const string& name) {

	return find(begin(excluded), end(excluded), name) != end(excluded);
}

void emit_code(const string& class_name, ostream& out, ostream& includes) {

	static bool is_first_pass = true;

    if (is_excluded(class_name)) {

    	return;
    }

   	if (is_first_pass) {

   		is_first_pass=false;
   	}
   	else {
   		out << ",\n"; // closes the previous line
   	}

   	includes << "#include \"" << class_name << ".hpp\"" << endl;

   	out<<"{ \""<<class_name<<"\", make_unique<"<<class_name<<">() }";
}

int main(int argc, char* argv[]) {

	path dir_path(argv[1]);

	if (!exists(dir_path) || !is_directory(dir_path)) {

		cerr << "Path \"" << argv[1] << "\" is not a valid directory" << endl;

		return 1;
	}

	ofstream classes( argv[1]+name_classes);

	ofstream includes(argv[1]+name_includes);

	for(directory_iterator i(argv[1]), end_itr; i != end_itr; ++i)	{

	    if (!is_regular_file(i->status()) || (i->path().extension()!=".hpp")) {

	    	continue;
	    }

	    string name = basename(i->path().filename());

	    emit_code(name, classes, includes);
	}

    cout << endl;
}



