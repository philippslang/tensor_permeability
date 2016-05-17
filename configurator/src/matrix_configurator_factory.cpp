#include "matrix_configurator_factory.h"
#include "uniform_matrix_configurator.h"

namespace csmp {
	namespace tperm {

		std::unique_ptr<Configurator> MatrixConfiguratorFactory::configurator(const Settings& settings, Configurator::Model& model) const
		{
			std::unique_ptr<Configurator> pConf(nullptr);
			return pConf;
		}

	} // !tperm
} // ! csmp