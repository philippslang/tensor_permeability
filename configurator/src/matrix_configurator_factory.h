#ifndef TP_MATRIXCONFIGFACT_H
#define TP_MATRIXCONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {
	namespace tperm {

		/// Makes matrix configurators from settings.
		class MatrixConfiguratorFactory : public ConfiguratorFactory
		{
		public:
			MatrixConfiguratorFactory();
			virtual ~MatrixConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&) const;
		};

	} // !tperm
} // !csmp

#endif // !TP_MATRIXCONFIGFACT_H