#include "catch.hpp"
#include "settings.h"

#include <string>

using namespace csmp::tperm;

TEST_CASE("settings unit test") {
	using T = double;
	std::string jname("setting one");
	T jval(1.);
	Settings s;	
	REQUIRE(s.json.count(jname) == 0);
	s.json[jname.c_str()] = jval;
	REQUIRE(s.json.count(jname) == 1);
	const T r = s.json[jname];
	REQUIRE(s.json[jname].get<T>() == jval);
	REQUIRE(r == jval);
}
