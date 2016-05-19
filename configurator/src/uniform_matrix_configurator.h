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

		/** \class UniformMatrixConfigurator

		Configures a homogeneous matrix for the entire model. Requires the configuration to be set to
			"matrix": {
				"configuration": "uniform"
			}

		## Keywords
		Matrix permeability can be assigned as a scalar (isotroppic) and as a tensor (diagonal and full tensor).

		### Isotropic permeability (spherical tensor)
		If `permeability' is a single flow, isotropic permeability is imposed.
			"matrix": {
				"configuration": "uniform",
				"permeability": 1.0E-15
			}

		### Anisotropic permeability (diagonal tensor)
		In this case, `permability' is a list containing `[k_xx, k_yy, k_zz]' in order, with respect to global coordinates.
			"matrix": {
				"configuration": "uniform",
				"permeability": [1.0E-15, 5.0E-15, 10.0E-15]
			}

		### Anisotropic permeability (full tensor)
		In this case, `permability' is a list containing `[k_xx, k_xy, k_xz, k_yx, k_yy, k_yz, k_zx, k_zy, k_zz]' in order, with respect to global coordinates.
			"matrix": {
				"configuration": "uniform",
				"permeability": [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]
			}

		*/

	} // !tperm
} // !csmp

#endif // !TP_UNIFMATRIXCONFIG_H