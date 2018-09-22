/** @file */

#ifndef TP_CONFIGFACT_H
#define TP_CONFIGFACT_H

#include <memory>
#include <vector>

namespace csmp {
template <size_t> class TensorVariable;

namespace tperm {
// forwards
class Settings;
class Configurator;

/// ABC for tperm::Configurator factory pattern
class ConfiguratorFactory {
public:
  ConfiguratorFactory();
  virtual ~ConfiguratorFactory();

  virtual std::unique_ptr<Configurator>
  configurator(const Settings &) const = 0;
};

/** \class ConfiguratorFactory

@todo Replace by function style factories

Primarily, ConfiguratorFactory instances decouples
tperm::Configurator from application tperm::Settings.
Secondly, they check user settings correctness to instantiate
Conifgurator objects, and check these
settings before the model is loaded and the Conifgurator applied.
*/

/// Generates a tensor from a tperm::Settings entry
csmp::TensorVariable<3> tensor(const char *vname, const Settings &);

/// Generates a tensor from a vector
csmp::TensorVariable<3> tensor(const std::vector<double> &);

} // !tperm
} // !csmp

#endif // !TP_CONFIGFACT_H