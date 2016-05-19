#include "matrix_configurator_factory.h"
#include "uniform_matrix_configurator.h"
#include "settings.h"
#include <string>
#include <TensorVariable.h>

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
			const string c = s["matrix configuration"].get<string>();

			if (c == string("uniform matrix")) {
				const TensorVariable<3> mperm;
				pConf.reset(new UniformMatrixConfigurator(mperm));
			}
			else if (0) {
				int x;
			}
			
			return pConf;
		}

	} // !tperm
} // ! csmp