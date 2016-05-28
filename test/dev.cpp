#include <fstream>

#include "catch.hpp"
#include "settings.h"
#include "json.hpp"
#include "model_io.h"
#include "matrix_configurator_factory.h"
#include "fracture_configurator_factory.h"
#include "configurator.h"
#include "sort_boundaries.h"
#include "pressure_solver.h"
#include "omega_configurator_factory.h"

#include "Model.h"
#include "TensorVariable.h"

using namespace csmp;
using namespace csmp::tperm;
using namespace std;


TEST_CASE("reading base configuration file") {
	std::ifstream f("config.json");
	Settings s;
	CHECK_NOTHROW(s.json << f);
	auto jconfig = s.json["configuration"];
	REQUIRE(jconfig["matrix"]["configuration"].get<string>() == string("uniform"));
}


TEST_CASE("model factory nullptr") {
	Settings ms;
	ms.json = R"({
                     "file name": "debug",
					 "format": "none"
				})"_json;
	auto nomodel = load_model(ms);
	REQUIRE(nomodel == nullptr);
}


TEST_CASE("tensor extraction") {
	Settings cs;
	cs.json = R"({
					"tensor": 1.0,
					"tensor diagonal": [1.0, 2.0, 3.0],
					"tensor full": [1.0, 0.1, 0.1, 0.2, 2.0, 0.2, 0.3, 0.3, 3.0]
				})"_json;
	// Spherical tensor
	REQUIRE(tensor("tensor", cs) == TensorVariable<3>(PLAIN, 1.0, 0., 0., 0., 1.0, 0., 0., 0., 1.0));
	// Diagonal tensor
	cs.json["tensor"] = {1.0, 2.0, 3.0};
	TensorVariable<3> td(PLAIN, 1.0, 0., 0., 0., 2.0, 0., 0., 0., 3.0);
	REQUIRE(tensor("tensor", cs) == td);
	REQUIRE(tensor("tensor diagonal", cs) == td);
	// Full tensor
	cs.json["tensor"] = { 1.0, 0.1, 0.1, 0.2, 2.0, 0.2, 0.3, 0.3, 3.0 };
	TensorVariable<3> tf(PLAIN, 1.0, 0.1, 0.1, 0.2, 2.0, 0.2, 0.3, 0.3, 3.0);
    REQUIRE(tensor("tensor full", cs) == tf);
	REQUIRE(tensor("tensor", cs) == tf);
}


TEST_CASE("flow tdd") {
	// generate settings
	Settings s;
	s.json = R"({
				 "model": {
                     "file name": "debug",
					 "format": "icem"
                 },
				 "configuration": {
				     "matrix":{
				         "configuration": "uniform",
						 "permeability": 1.0E-15
					 },
					 "fractures":{
						 "configuration": "uniform",
						 "mechanical aperture": 0.01, 
						 "hydraulic aperture": 0.001
					 }
				 },
				"analysis":{
					"configuration": "uniform boundary distance",
					"distance": 1.0
				}
				})"_json;

	// get matrix configurator
	Settings mcs(s.json["configuration"]["matrix"]);
	MatrixConfiguratorFactory mcf;
	auto mconf = mcf.configurator(mcs);
	// get fracture configurator
	Settings fcs(s.json["configuration"]["fractures"]);
	FractureConfiguratorFactory fcf;
	auto fconf = fcf.configurator(fcs);
	// get omega generator
	Settings acs(s.json["analysis"]);
	OmegaConfiguratorFactory ocf;
	auto oconf = ocf.configurator(acs);

	if (1) { 
		// load model...		
		Settings ms(s.json["model"]);
		auto model = load_model(ms);
		// configure material properties
		mconf->configure(*model);
		fconf->configure(*model);
		// compute conductivity
		conductivity(*model);
		// sort boundaries
		auto bds = sort_boundaries(*model, s);
		// ready to solve
		solve(bds, *model);
		// generate omegas
		oconf->configure(*model);
	}
}

