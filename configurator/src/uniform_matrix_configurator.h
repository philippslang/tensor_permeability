#ifndef TP_UNIFMATRIXCONFIG_H
#define TP_UNIFMATRIXCONFIG_H

#include "configurator.h"

namespace csmp {


	namespace tperm {

		/// Configures uniform matrix.
		class UniformMatrixConfigurator : public Configurator
		{
		public:
			typedef csmp::Model<3> Model;

			UniformMatrixConfigurator(Model&);

			virtual bool configure() const;
		};

	} // !tperm
} // !csmp

#endif // !TP_UNIFMATRIXCONFIG_H