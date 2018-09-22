#include "null_configurator.h"

namespace csmp {
namespace tperm {

NullConfigurator::NullConfigurator() {}

NullConfigurator::~NullConfigurator() {}

bool NullConfigurator::configure(Model &m) const { return true; }

} // !tperm
} // ! csmp