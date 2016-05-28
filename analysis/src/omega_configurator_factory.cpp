#include "omega_configurator_factory.h"
#include "omega_bdistance_configurator.h"
#include "settings.h"
#include <string>
#include <TensorVariable.h>

using namespace std;

namespace csmp {
	namespace tperm {


		OmegaConfiguratorFactory::OmegaConfiguratorFactory()
			: ConfiguratorFactory()
		{
		}


		OmegaConfiguratorFactory::~OmegaConfiguratorFactory()
		{
		}


		/**
		Returns nullptr if settings incorrect.
		*/
		std::unique_ptr<Configurator> OmegaConfiguratorFactory::configurator(const Settings& s) const
		{
			std::unique_ptr<Configurator> pConf(nullptr);
			const string c = s.json["configuration"].get<string>();

			if (c == string("uniform boundary distance")) {
				const double dist = s.json["distance"].get<double>();
				pConf.reset(new OmegaBDistanceConfigurator(dist));
			}
			else if (0) {
			}
			return pConf;
		}


	} // !tperm
} // ! csmp