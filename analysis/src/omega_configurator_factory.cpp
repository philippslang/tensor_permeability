#include "omega_configurator_factory.h"
#include "omega_bdistance_configurator.h"
#include "omega_corner_points_configurator.h"
#include "settings.h"
#include <TensorVariable.h>
#include <string>

using namespace std;

namespace csmp {
namespace tperm {

OmegaConfiguratorFactory::OmegaConfiguratorFactory() : ConfiguratorFactory() {}

OmegaConfiguratorFactory::~OmegaConfiguratorFactory() {}

/**
Returns nullptr if settings incorrect.
@todo check input for bounding box coords
*/
std::unique_ptr<Configurator>
OmegaConfiguratorFactory::configurator(const Settings &s) const {
  std::unique_ptr<Configurator> pConf(nullptr);
  const string c = s.json["configuration"].get<string>();

  if (c == (string) "uniform boundary distance") {
    const double dist = s.json["distance"].get<double>();
    pConf.reset(new OmegaBDistanceConfigurator(dist));
  } else if (c == (string) "bounding box") {
    auto boxes = s.json["corner points"].get<vector<vector<vector<double>>>>();
    vector<array<csmp::Point<3>, 2>> omega_bcoords;
    for (size_t o(0); o < boxes.size(); ++o)
      omega_bcoords.push_back(
          {csmp::Point<3>(boxes.at(o).at(0).at(0), boxes.at(o).at(0).at(1),
                          boxes.at(o).at(0).at(2)),
           csmp::Point<3>(boxes.at(o).at(1).at(0), boxes.at(o).at(1).at(1),
                          boxes.at(o).at(1).at(2))});
    pConf.reset(new OmegaCornerPointsConfigurator(omega_bcoords));
  }
  return pConf;
}

} // !tperm
} // ! csmp