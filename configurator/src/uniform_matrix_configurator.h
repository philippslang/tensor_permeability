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
			UniformMatrixConfigurator() = delete;
			/// Allowing for full tensor to be specified
			explicit UniformMatrixConfigurator(const csmp::TensorVariable<3>&);
			/// Spherical tensor, i.e. isotropic permeability
			explicit UniformMatrixConfigurator(double);

			virtual bool configure(Model&) const;

		private:
			const csmp::TensorVariable<3> perm_;
		};

		/** \class UniformMatrixConfigurator

		Configures equidimensional elements to a uniform `permeability` (m2) and `conductivity` (m2/Pa.s) for a 3D model.

		The following variables are initialized by the provided configurators:

		conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
		permeability	pe	m2	3	1e-25	1e-08	ELEMENT
		*/

	} // !tperm
} // !csmp

#endif // !TP_UNIFMATRIXCONFIG_H