#ifndef TP_MATRIXCONFIGFACT_H
#define TP_MATRIXCONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {
	namespace tperm {

		/// Makes matrix configurators.
		class MatrixConfiguratorFactory
		{
			MatrixConfiguratorFactory();
			virtual ~MatrixConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&) const;
		};

	} // !tperm
} // !csmp

#endif // !TP_MATRIXCONFIGFACT_H