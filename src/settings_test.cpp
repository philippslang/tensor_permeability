#include "catch.hpp"
#include "settings.h"

#include <string>

using namespace csmp::tperm;

TEST_CASE("settings unit test") {
	using T = double;
	std::string jname("setting one");
	T jval(1.);
	Settings s;	
	s[jname.c_str()] = jval;
}
