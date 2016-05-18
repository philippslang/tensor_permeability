#include <fstream>

#include "catch.hpp"
#include "settings.h"

using namespace csmp::tperm;
using namespace std;

TEST_CASE("reading base configuration file") {

	std::ifstream f("config.json");
	Settings j;
	CHECK_NOTHROW(j << f);
	REQUIRE(j["configuration"].get<string>() == string("uniform matrix"));
}

