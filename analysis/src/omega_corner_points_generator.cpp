#include "omega_corner_points_generator.h"
#include "dfn_omega.h"
#include "model_io.h"
#include "omega.h"

#include "Model.h"

using namespace std;

namespace csmp {
namespace tperm {

OmegaCornerPointsGenerator::OmegaCornerPointsGenerator(
    const std::vector<std::array<csmp::Point<3>, 2>> &cpts)
    : cpts_(cpts) {}

OmegaCornerPointsGenerator::~OmegaCornerPointsGenerator() {}

OmegaCornerPointsGenerator::OmegaPtrColl
OmegaCornerPointsGenerator::generate(const csmp::Model<3> &m) const {
  OmegaPtrColl ptrs(cpts_.size());
  const Index am_key(m.Database().StorageKey("mechanical aperture"));

  size_t i(0);
  Point<3> ebc;
  for (const auto &cpp : cpts_) {
    auto cmm = min_max(cpp);
    vector<csmp::Element<3> *> ePtrs;
    ePtrs.reserve(m.Region("Model").Elements());
    for (const auto &eit : m.Region("Model").ElementVector()) {
      ebc = eit->BaryCenter();
      if (!within_bounds(ebc, cmm))
        continue;           // not within min-max bounds
      ePtrs.push_back(eit); // is within min-max bounds
    }
    Omega o = omega_from_elements(ePtrs, am_key);
    if (!is_dfn(m))
      ptrs[i] = make_shared<Omega>(o);
    else
      ptrs[i] = make_shared<DfnOmega>(o, total_volume(cmm));
    ++i;
  }
  return ptrs;
}

} // ! tperm
} // !csmp