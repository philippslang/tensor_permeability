#ifndef TP_OMEGACONFIGFACT_H
#define TP_OMEGACONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {

namespace tperm {

/// Makes sampling region configurators from settings
class OmegaConfiguratorFactory : public ConfiguratorFactory {
public:
  OmegaConfiguratorFactory();
  virtual ~OmegaConfiguratorFactory();

  virtual std::unique_ptr<Configurator>
  configurator(const Settings &) const override;
};

/** \class OmegaConfiguratorFactory

@deprecated We don't use omega configurators - look for the
equivalent function factory

Creates Configurator for the sampling region creation.

## Single omega region, uniform distance from all model boundaries

Creates a single sampling region `omega` that contains all elements
that `5.0` [L] away from all (physical)
model boundaries:

        "configuration": "uniform boundary distance",
        "distance": 5.0

## N omega regions, bounding box concept with corner coordinates

Creates 0 to N-1 `omega_0...N-1` regions for each pair of corner
points provided:

        "configuration": "bounding box",
        "corner points": [[[0.0,0.0,0.0],[1.0,1.0,1.0]],
[[5.0,5.0,5.0],[10.0,10.0,10.0]]]

Here, `omega_0` will be a region within [0.0,0.0,0.0] (as in xyz)
and [1.0,1.0,1.0], and `omega_1`
in between [5.0,5.0,5.0] and [10.0,10.0,10.0].

Sampling regions creates here are independent, i.e. they can
overlap. Useful also for scaling investigations, i.e.
congruent regions of increasing size.

*/

} // !tperm
} // !csmp

#endif // !TP_OMEGACONFIGFACT_H