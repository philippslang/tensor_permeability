#include "regional_uniform_fracture_configurator.h"
#include "bpreds.h"
#include "elops.h"
#include "ttrans.h"

#include "Model.h"

#include <stdexcept>

using namespace std;

namespace csmp {
namespace tperm {

/**
This ctor causes subsequently that all fracture elements of the same
region hold the same hydraulic aperture tensor, thus need to have the same
orientation in space. The tensor needs to reflect that the fracture
normal direction aperture is zero, and that the eigenvalues
are aligned in the fracture plane, plus the unormal. Because this
might be a rotated tensor, we need aperture, permeability (ah^2/12, then
rotated)
and conductivity (ah^3/12, then rotated) in full tensor form for
each region.
*/
RegionalUniformFractureConfigurator::RegionalUniformFractureConfigurator(
    const vector<csmp::TensorVariable<3>> &ahs,
    const vector<csmp::TensorVariable<3>> &ks,
    const vector<csmp::TensorVariable<3>> &cs, const vector<double> &ams,
    const vector<string> &rnames)
    : UniformFractureConfigurator(csmp::TensorVariable<3>(PLAIN, 0.),
                                  csmp::TensorVariable<3>(PLAIN, 0.),
                                  csmp::TensorVariable<3>(PLAIN, 0.), 0.),
      ams_(ams), frnames_(rnames), ahs_(ahs), ks_(ks), cs_(cs) {
  check_vsize();
}

/**
            Attention: Expensive version. Subsequently this causes for all
   fracture elements in one region to have their unit normal
            evaluated. For a faster version, do the transformation manually and
   specify the Tensor as is for trivial fracture geometries.
            */
RegionalUniformFractureConfigurator::RegionalUniformFractureConfigurator(
    const vector<double> &ahs, const vector<double> &ams,
    const vector<string> &rnames)
    : UniformFractureConfigurator(0., 0.), ams_(ams), frnames_(rnames),
      ahs_(ahs.size(), this->ah_), ks_(ahs.size(), this->ah_),
      cs_(ahs.size(), this->ah_) {
  for (size_t i(0); i < ahs.size(); ++i)
    ahs_[i] = csmp::TensorVariable<3>(PLAIN, ahs[i], 0., 0., 0., ahs[i], 0., 0.,
                                      0., 0.);
  check_vsize();
}

void RegionalUniformFractureConfigurator::check_vsize() const {
  const size_t r(ahs_.size());
  if (r == ams_.size())
    if (r == frnames_.size())
      return;
  throw runtime_error(
      "Vectors for regional fracture configuration are not of uniform length");
}

/**
            Assigns uniform transmissivity for each provided region. Depending
   on the construction, this
            either assigns the tensor as is or computes a projection. Relies on
   the following variables, which are set in here

                    hydraulic aperture	hy	m	3	0	1
   ELEMENT
                    mechanical aperture	me	m	1	0	1
   ELEMENT
                    conductivity	co	m2 Pa-1 s-1	3	1e-25	1
   ELEMENT
                    permeability	pe	m2	3	1e-25	1e-08
   ELEMENT

            Assumes unit viscosity.
            */
bool RegionalUniformFractureConfigurator::configure(Model &model) const {
  for (size_t r(0); r < ahs_.size(); ++r) {
    auto felmts =
        model.ElementsFrom(FractureElement<3>(false), frnames_[r].c_str());
    input_am(model, felmts, ams_[r]);
    if (!this->project_)
      direct_ah(model, felmts, ahs_[r], ks_[r], cs_[r]);
    else
      project_ah(model, felmts, ahs_[r]);
  }
  return true;
}

} // !tperm
} // ! csmp