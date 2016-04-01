#include <fstream>

#include "catch.hpp"
#include "json.hpp"

using json = nlohmann::json;

TEST_CASE("reading base configuration file") {

	std::ifstream f("config.json");
	json j;
	CHECK_NOTHROW(j << f);
}

