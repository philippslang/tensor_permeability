#include "matrix_configurator_factory.h"
#include "settings.h"
#include "uniform_matrix_configurator.h"
#include <TensorVariable.h>
#include <string>

using namespace std;

namespace csmp {
namespace tperm {

MatrixConfiguratorFactory::MatrixConfiguratorFactory()
    : ConfiguratorFactory() {}

MatrixConfiguratorFactory::~MatrixConfiguratorFactory() {}

/**
Returns nullptr if settings incorrect.
*/
std::unique_ptr<Configurator>
MatrixConfiguratorFactory::configurator(const Settings &s) const {
  std::unique_ptr<Configurator> pConf(nullptr);
  const string c = s.json["configuration"].get<string>();

  if (c == string("uniform")) {
    const TensorVariable<3> mperm = tensor("permeability", s);
    pConf.reset(new UniformMatrixConfigurator(mperm));
  } else if (0) {
  }
  return pConf;
}

} // !tperm
} // ! csmp