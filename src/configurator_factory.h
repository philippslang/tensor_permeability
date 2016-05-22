#ifndef TP_CONFIGFACT_H
#define TP_CONFIGFACT_H

#include <memory>

namespace csmp {
	namespace tperm {
		// forwards
		class Settings;
		class Configurator;

		/// ABC for tperm::Configurator factory pattern
		class ConfiguratorFactory
		{
		public:
			ConfiguratorFactory();
			virtual ~ConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&) const = 0;
		};

		/** \class ConfiguratorFactory

		Primarily, ConfiguratorFactory instances decouples tperm::Configurator from application tperm::Settings.
		*/

	} // !tperm
} // !csmp

#endif // !TP_CONFIGFACT_H