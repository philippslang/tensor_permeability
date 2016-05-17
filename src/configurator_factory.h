#ifndef TP_CONFIGFACT_H
#define TP_CONFIGFACT_H

#include "configurator.h"
#include <memory>

namespace csmp {
	namespace tperm {
		// forwards
		class Settings;

		/// ABC for tperm::Configurator factory pattern.
		class ConfiguratorFactory
		{
			ConfiguratorFactory();
			virtual ~ConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&, Configurator::Model&) const = 0;
		};

	} // !tperm
} // !csmp

#endif // !TP_CONFIGFACT_H