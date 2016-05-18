#include "matrix_configurator_factory.h"
#include "uniform_matrix_configurator.h"
#include "settings.h"
#include <string>

using namespace std;

namespace csmp {
	namespace tperm {

		MatrixConfiguratorFactory::MatrixConfiguratorFactory()
			: ConfiguratorFactory()
		{
		}


		MatrixConfiguratorFactory::~MatrixConfiguratorFactory()
		{
		}

		std::unique_ptr<Configurator> MatrixConfiguratorFactory::configurator(const Settings& s) const
		{
			std::unique_ptr<Configurator> pConf(nullptr);
			const auto c = s["matrix configuration"].get<string>();
			return pConf;
		}

	} // !tperm
} // ! csmp