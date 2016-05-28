#ifndef TP_OMEGACONFIGFACT_H
#define TP_OMEGACONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {

	namespace tperm {

		/// Makes sampling region configurators from settings
		class OmegaConfiguratorFactory : public ConfiguratorFactory
		{
		public:
			OmegaConfiguratorFactory();
			virtual ~OmegaConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&) const;
		};


		/** \class OmegaConfiguratorFactory

		Creates Configurator for the sampling region creation.

		## Single omega region, uniform distance from all model boundaries

		Creates a single sampling region `omega` that contains all elements that `5.0` [L] away from all (physical)
		model boundaries:

			"configuration": "uniform boundary distance",
			"distance": 5.0

		*/

	} // !tperm
} // !csmp

#endif // !TP_OMEGACONFIGFACT_H