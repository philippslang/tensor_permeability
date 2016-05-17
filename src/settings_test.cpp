#include "catch.hpp"
#include "settings.h"

#include <string>

using namespace csmp::tperm;

TEST_CASE("settings unit test") {
	using T = double;
	std::string jname("setting one");
	T jval(1.);
	Settings s;	
	REQUIRE(s.count(jname) == 0);
	s[jname.c_str()] = jval;
	REQUIRE(s.count(jname) == 1);
	const T r = s[jname];
	REQUIRE(s[jname].get<T>() == jval);
	REQUIRE(r == jval);
}
