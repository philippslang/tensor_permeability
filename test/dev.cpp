#include <fstream>

#include "catch.hpp"
#include "settings.h"
#include "json.hpp"
#include "model_io.h"

#include "Model.h"

using namespace csmp::tperm;
using namespace std;


TEST_CASE("reading base configuration file") {
	std::ifstream f("config.json");
	Settings s;
	CHECK_NOTHROW(s.json << f);
	auto jconfig = s.json["configuration"];
	REQUIRE(jconfig["matrix"]["configuration"].get<string>() == string("uniform"));
}


TEST_CASE("uniform matrix configuration") {
	Settings s;
	s.json = R"({
				 "model": {
                     "file name": "debug"
                 },
				 "configuration": {
				     "matrix":{
				         "configuration": "uniform"
					 }
				 }
				})"_json;
	Settings ms(s.json["model"]);
	//Settings ms;
	//ms.json = s.json["model"];
	auto model = load_model(ms);
}

