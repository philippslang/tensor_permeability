#include "omega_bdistance_generator.h"
#include "dfn_omega.h"
#include "model_io.h"
#include "omega.h"

#include "Model.h"
#include "Point.h"

using namespace std;

namespace csmp {
namespace tperm {

OmegaBDistanceGenerator::OmegaBDistanceGenerator() : dist_(0.) {}

OmegaBDistanceGenerator::OmegaBDistanceGenerator(double dist) : dist_(dist) {}

OmegaBDistanceGenerator::~OmegaBDistanceGenerator() {}

double OmegaBDistanceGenerator::sampling_box_total_volume(
    const csmp::Model<3> &m) const {
  std::array<csmp::Point<3>, 2> cmm;
  m.MinMaxCoordinates(cmm[0], cmm[1]);
  cmm[0] += dist_;
  cmm[1] -= dist_;
  return this->total_volume(cmm);
}

OmegaBDistanceGenerator::OmegaPtrColl
OmegaBDistanceGenerator::generate(const csmp::Model<3> &m) const {
  csmp::Point<3> ebc;
  vector<csmp::Element<3> *> ePtrs;
  ePtrs.reserve(m.Region("Model").Elements());
  for (const auto &eit : m.Region("Model").ElementVector()) {
    ebc = eit->BaryCenter();
    double dmin = numeric_limits<double>::max();
    for (auto bit = m.BoundariesBegin(); bit != m.BoundariesEnd(); ++bit) {
      if (!is_main_boundary_id(bit->first.second))
        continue;
      for (const auto &bnit : bit->second.NodeVector()) {
        double const dist = ebc.DistanceTo(bnit->Coordinate());
        if (dist < dmin)
          dmin = dist;
      }
    }
    if (dmin >= dist_)
      ePtrs.push_back(eit);
  }

  OmegaPtrColl ptrs(1, nullptr);
  const Index am_key(m.Database().StorageKey("mechanical aperture"));
  auto o = omega_from_elements(ePtrs, am_key);
  if (!is_dfn(m))
    ptrs[0] = make_shared<Omega>(o);
  else
    ptrs[0] = make_shared<DfnOmega>(o, sampling_box_total_volume(m));
  return ptrs;
}

} // ! tperm
} // !csmp