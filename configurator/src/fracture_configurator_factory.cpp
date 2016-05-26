#include "fracture_configurator_factory.h"
#include "uniform_fracture_configurator.h"
#include "settings.h"
#include <string>
#include <TensorVariable.h>

using namespace std;

namespace csmp {
	namespace tperm {


		FractureConfiguratorFactory::FractureConfiguratorFactory()
			: ConfiguratorFactory()
		{
		}


		FractureConfiguratorFactory::~FractureConfiguratorFactory()
		{
		}


		/**
		Returns nullptr if settings incorrect.
		*/
		std::unique_ptr<Configurator> FractureConfiguratorFactory::configurator(const Settings& s) const
		{
			std::unique_ptr<Configurator> pConf(nullptr);
			const string c = s.json["configuration"].get<string>();

			if (c == string("uniform")) {
				const double am = s.json["mechanical aperture"].get<double>();
				if (s.json["hydraulic aperture"].size() == 9) // tensor
					pConf.reset(new UniformFractureConfigurator(tensor("hydraulic aperture", s), am));
				else // scalar
					pConf.reset(new UniformFractureConfigurator(s.json["hydraulic aperture"].get<double>(), am));
			}
			else if (0) {
			}
			return pConf;
		}


	} // !tperm
} // ! csmp