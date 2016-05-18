#ifndef TP_UNIFMATRIXCONFIG_H
#define TP_UNIFMATRIXCONFIG_H

#include "configurator.h"
#include "TensorVariable.h"


namespace csmp {

	namespace tperm {

		/// Configures uniform matrix.
		class UniformMatrixConfigurator : public Configurator
		{
		public:
			UniformMatrixConfigurator(const csmp::TensorVariable<3>&);

			virtual bool configure(Model&) const;

		private:
			csmp::TensorVariable<3> perm_;
		};

	} // !tperm
} // !csmp

#endif // !TP_UNIFMATRIXCONFIG_H