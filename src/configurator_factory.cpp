#include "configurator_factory.h"

#include "TensorVariable.h"
#include "settings.h"

namespace csmp {
namespace tperm {

ConfiguratorFactory::ConfiguratorFactory() {}

ConfiguratorFactory::~ConfiguratorFactory() {}

/// Column-major ordering
csmp::TensorVariable<3> tensor(const std::vector<double> &v) {
  TensorVariable<3> t(PLAIN, 0.);
  for (size_t i(0); i < 3; ++i)
    for (size_t k(0); k < 3; ++k)
      t(i, k) = v.at(i * 3 + k);
  return t;
}

/**
Returns a csmp::TensorVariable<3> based on a settings entry. This
`entry` can take multiple forms

### Spherical tensor (scalar value)

        "entry": 1.0

### Diagonal tensor (list of 3)

        "entry": [1.0, 2.0, 3.0]

### Full tensor (list of 9)
Column-major order.

        "entry": [1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 3.0]

Returns a null tensor if settings invalid.
*/
csmp::TensorVariable<3> tensor(const char *entry, const Settings &s) {
  TensorVariable<3> t(PLAIN, 0.);
  const auto j = s.json[entry];
  if (j == nullptr)
    throw json_null(entry);
  const size_t si = j.size();
  if (si == 1)
    t(0, 0) = t(1, 1) = t(2, 2) = j.get<double>();
  else if (si == 3)
    for (size_t i(0); i < 3; ++i)
      t(i, i) = j[i].get<double>();
  else if (si == 9)
    for (size_t i(0); i < 3; ++i)
      for (size_t k(0); k < 3; ++k)
        t(i, k) = j[i * 3 + k].get<double>();
  return t;
}

} // !tperm
} // ! csmp