#include <fstream>

#include "Model.h"
#include "TensorVariable.h"
#include "catch.hpp"
#include "configurator.h"
#include "fetch.h"
#include "fracture_configurator_factory.h"
#include "json.hpp"
#include "make_omega_generator.h"
#include "matrix_configurator_factory.h"
#include "model_io.h"
#include "omega_configurator_factory.h"
#include "omega_generator.h"
#include "pressure_solver.h"
#include "report.h"
#include "run.h"
#include "settings.h"
#include "sort_boundaries.h"

using namespace csmp;
using namespace csmp::tperm;
using namespace std;

#define TP_EXTENDED_TESTS 0

TEST_CASE("reading base configuration file") {
  std::ifstream f("config.json");
  REQUIRE(f.is_open());
  Settings s;
  REQUIRE_NOTHROW(s.json << f);
  f.close();
  auto jconfig = s.json["configuration"];
  REQUIRE(jconfig["matrix"]["configuration"].get<string>() ==
          string("uniform"));
}

TEST_CASE("running from file") {
  if (TP_EXTENDED_TESTS)
    run("settings.json");
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
  REQUIRE(tensor("tensor", cs) ==
          TensorVariable<3>(PLAIN, 1.0, 0., 0., 0., 1.0, 0., 0., 0., 1.0));
  // Diagonal tensor
  cs.json["tensor"] = {1.0, 2.0, 3.0};
  TensorVariable<3> td(PLAIN, 1.0, 0., 0., 0., 2.0, 0., 0., 0., 3.0);
  REQUIRE(tensor("tensor", cs) == td);
  REQUIRE(tensor("tensor diagonal", cs) == td);
  // Full tensor
  cs.json["tensor"] = {1.0, 0.1, 0.1, 0.2, 2.0, 0.2, 0.3, 0.3, 3.0};
  TensorVariable<3> tf(PLAIN, 1.0, 0.1, 0.1, 0.2, 2.0, 0.2, 0.3, 0.3, 3.0);
  REQUIRE(tensor("tensor full", cs) == tf);
  REQUIRE(tensor("tensor", cs) == tf);
}

TEST_CASE("flow tdd minimal configuration") {
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
						 "mechanical aperture": 0.0001, 
						 "hydraulic aperture": 0.0001
					 }
				 },
				"analysis":{
					"configuration": "uniform boundary distance",
					"distance": 2.0
				}
				})"_json;

  // get matrix configurator
  Settings mcs(Settings(s, "configuration"), "matrix");
  MatrixConfiguratorFactory mcf;
  auto mconf = mcf.configurator(mcs);
  // get fracture configurator
  Settings fcs(Settings(s, "configuration"), "fractures");
  FractureConfiguratorFactory fcf;
  auto fconf = fcf.configurator(fcs);
  // get omega generator
  Settings acs(s, "analysis");
  OmegaConfiguratorFactory ocf;
  auto oconf = ocf.configurator(acs);

  if (TP_EXTENDED_TESTS) {
    REQUIRE_NOTHROW(run(s));
  }
}

TEST_CASE("flow tdd extended configuration") {
  // generate settings
  Settings s;
  s.json = R"({
				 "model": {
                     "file name": "debug",
					 "format": "icem",
					 "regions": ["CREATED_MATERIAL_9", "FRACTURES", "BOUNDARY1", "BOUNDARY2", "BOUNDARY3", "BOUNDARY4", "BOUNDARY5", "BOUNDARY6"]
                 },
				 "configuration": {
				     "matrix":{
				         "configuration": "uniform",
						 "permeability": 1.0E-15
					 },
					 "fractures":{
						 "configuration": "regional uniform",
						 "fracture regions": ["FRACTURES"],
						 "mechanical aperture": [0.0001], 
						 "hydraulic aperture": [0.0001]
					 }
				 },
				"analysis":{
					"configuration": "bounding box",
					"corner points": [[[-3.0,-3.0,2.0],[3.0,3.0,8.0]], [[-2.0,-2.0,3.0],[2.0,2.0,7.0]]]
				}
				})"_json;

  // get matrix configurator
  Settings mcs(Settings(s, "configuration"), "matrix");

  MatrixConfiguratorFactory mcf;
  auto mconf = mcf.configurator(mcs);
  // get fracture configurator
  Settings fcs(Settings(s, "configuration"), "fractures");
  auto fconf = FractureConfiguratorFactory().configurator(fcs);

  // get omega generator
  Settings acs(s, "analysis");
  OmegaConfiguratorFactory ocf;
  auto oconf = ocf.configurator(acs);

  if (TP_EXTENDED_TESTS) {
    REQUIRE_NOTHROW(run(s));
  }
}

TEST_CASE("omega maker tdd") {
  Settings s;
  s.json = R"({
				 "model": {
                     "file name": "debug",
					 "format": "icem",
					 "regions": ["CREATED_MATERIAL_9", "BOUNDARY1", "BOUNDARY2", "BOUNDARY3", "BOUNDARY4", "BOUNDARY5", "BOUNDARY6"]
                 },
				"analysis":{
					"configuration": "bounding box",
					"corner points": [[[-3.0,-3.0,2.0],[3.0,3.0,8.0]], [[-2.0,-2.0,3.0],[2.0,2.0,7.0]]]
				}
				})"_json;

  Settings acs(s, "analysis");
  auto ogen = make_omega_generator(acs);
  Settings mcs(s, "model");
  if (TP_EXTENDED_TESTS) {
    auto model = load_model(mcs);
    REQUIRE(model != nullptr);
    auto omegas = ogen->generate(*model);
    REQUIRE(omegas.size() == 2);
  }
}
