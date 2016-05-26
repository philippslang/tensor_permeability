#ifndef TP_MATRIXCONFIGFACT_H
#define TP_MATRIXCONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {

	namespace tperm {

		/// Makes matrix configurators from settings
		class MatrixConfiguratorFactory : public ConfiguratorFactory
		{
		public:
			MatrixConfiguratorFactory();
			virtual ~MatrixConfiguratorFactory();

			virtual std::unique_ptr<Configurator> configurator(const Settings&) const;
		};


		/** \class MatrixConfiguratorFactory

		Creates Configurator for the model matrix, i.e. all equi-dim elements.

		## Uniform

		Configures a homogeneous matrix for the entire model. Requires the configuration to be set to

			"configuration": "uniform"

		Matrix permeability can be assigned as a scalar (isotroppic) and as a tensor (diagonal and full tensor).

		### Isotropic permeability (spherical tensor)

		If `permeability` is a single float, isotropic permeability is imposed.

			"configuration": "uniform",
			"permeability": 1.0E-15

		### Anisotropic permeability (diagonal tensor)

		In this case, `permability` is a list containing `[k_xx, k_yy, k_zz]` in order, with respect to global coordinates

			"configuration": "uniform",
			"permeability": [1.0E-15, 5.0E-15, 10.0E-15]			

		### Anisotropic permeability (full tensor)

		In this case, `permability` is a list containing `[k_xx, k_xy, k_xz, k_yx, k_yy, k_yz, k_zx, k_zy, k_zz]` in order, with respect to global coordinates.

			"configuration": "uniform",
			"permeability": [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]

		*/

	} // !tperm
} // !csmp

#endif // !TP_MATRIXCONFIGFACT_H