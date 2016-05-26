#ifndef TP_UNIFMATRIXCONFIG_H
#define TP_UNIFMATRIXCONFIG_H

#include "configurator.h"
#include "TensorVariable.h"


namespace csmp {

	namespace tperm {

		/// Configures uniform matrix
		class UniformMatrixConfigurator : public Configurator
		{
		public:
			/// Allowing for full tensor to be specified
			UniformMatrixConfigurator(const csmp::TensorVariable<3>&);
			/// Spherical tensor, i.e. isotropic permeability
			UniformMatrixConfigurator(double);

			virtual bool configure(Model&) const;

		private:
			csmp::TensorVariable<3> perm_;
		};

		/** \class UniformMatrixConfigurator

		Configures equidimensional elements to a uniform `permeability` for a 3D model.
		*/

	} // !tperm
} // !csmp

#endif // !TP_UNIFMATRIXCONFIG_H