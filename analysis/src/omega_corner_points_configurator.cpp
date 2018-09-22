#include "omega_corner_points_configurator.h"

#include "Model.h"

using namespace std;

namespace csmp {
namespace tperm {

OmegaCornerPointsConfigurator::OmegaCornerPointsConfigurator(
    const vector<array<csmp::Point<3>, 2>> &cpts)
    : Configurator(), cpts_(cpts) {}

bool OmegaCornerPointsConfigurator::configure(Model &m) const {
  size_t i(0);
  Point<3> ebc;
  m.UpdateIndices();
  for (const auto &cpp : cpts_) {
    auto cmm = min_max(cpp);
    vector<size_t> omega_ids;
    omega_ids.reserve(m.Region("Model").Elements());
    for (const auto &eit : m.Region("Model").ElementVector()) {
      ebc = eit->BaryCenter();
      if (!within_bounds(ebc, cmm))
        continue;                      // not within min-max bounds
      omega_ids.push_back(eit->Idx()); // is within min-max bounds
    }
    auto rname = (string) "omega_" + to_string(i);
    ++i;
    if (omega_ids.size())
      m.FormRegionFrom(rname.c_str(), omega_ids);
  }
  return true;
}

} // !tperm
} // ! csmp