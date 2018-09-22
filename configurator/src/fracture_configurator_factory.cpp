#include "fracture_configurator_factory.h"
#include "regional_uniform_fracture_configurator.h"
#include "settings.h"
#include "uniform_fracture_configurator.h"
#include <TensorVariable.h>
#include <string>

using namespace std;

namespace csmp {
namespace tperm {

FractureConfiguratorFactory::FractureConfiguratorFactory()
    : ConfiguratorFactory() {}

FractureConfiguratorFactory::~FractureConfiguratorFactory() {}

/**
Returns nullptr if settings incorrect.
*/
std::unique_ptr<Configurator>
FractureConfiguratorFactory::configurator(const Settings &s) const {
  std::unique_ptr<Configurator> pConf(nullptr);
  const string c = s.json["configuration"].get<string>();

  if (c == string("uniform")) {
    const double am = s.json["mechanical aperture"].get<double>();
    if (s.json["hydraulic aperture"].size() == 9) // tensor
      pConf.reset(new UniformFractureConfigurator(
          tensor("hydraulic aperture", s), tensor("permeability", s),
          tensor("conductivity", s), am));
    else // scalar
      pConf.reset(new UniformFractureConfigurator(
          s.json["hydraulic aperture"].get<double>(), am));
  } else if (c == string("regional uniform")) {
    const auto ams = s.json["mechanical aperture"].get<vector<double>>();
    const auto frnames = s.json["fracture regions"].get<vector<string>>();
    if (s.json.count("permeability")) { // tensor
      vector<string> props = {"hydraulic aperture", "permeability",
                              "conductivity"};
      vector<vector<TensorVariable<3>>> vals(
          props.size(),
          vector<TensorVariable<3>>(ams.size(), TensorVariable<3>()));
      for (size_t i(0); i < props.size(); ++i) {
        auto jvals = s.json[props[i].c_str()].get<vector<vector<double>>>();
        for (size_t j(0); j < ams.size(); ++j)
          vals[i][j] = tensor(jvals.at(j));
      }
      pConf.reset(new RegionalUniformFractureConfigurator(
          vals.at(0), vals.at(1), vals.at(2), ams, frnames));
    } else { // scalar
      const auto ahs = s.json["hydraulic aperture"].get<vector<double>>();
      pConf.reset(new RegionalUniformFractureConfigurator(ahs, ams, frnames));
    }
  }
  return pConf;
}

} // !tperm
} // ! csmp