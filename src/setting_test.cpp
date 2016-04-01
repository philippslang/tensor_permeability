#include "catch.hpp"
#include "setting.h"

#include <string>

using json = nlohmann::json;
using namespace csmp::tperm;

TEST_CASE("setting unit test") {
	using T = double;
	std::string jname("setting one");
	T jval(1.);
	json j;	
	j[jname.c_str()] = jval;
	Setting s;
	REQUIRE(s.empty());
	REQUIRE_THROWS(s.value<T>());
	s.initialize(j);
	REQUIRE(s.value<T>() == jval);
}
