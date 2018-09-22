#ifndef TP_FRACCONFIGFACT_H
#define TP_FRACCONFIGFACT_H

#include "configurator_factory.h"

namespace csmp {

namespace tperm {

    /// Makes fracture configurators from settings
    class FractureConfiguratorFactory : public ConfiguratorFactory {
    public:
        FractureConfiguratorFactory();
        virtual ~FractureConfiguratorFactory();

        virtual std::unique_ptr<Configurator> configurator(const Settings&) const override;
    };

    /** \class FractureConfiguratorFactory

		Creates a Configurator for the model fractures, i.e. all lower-dim elements.

		## Uniform

		Configures homogeneous fractures for the entire model. Requires the configuration to be set to

			"configuration": "uniform",
			"mechanical aperture: 1.0

		Fracture `hydraulic aperture` can be assigned as a scalar (isotroppic) and as a tensor (full tensor). The `mechanical aperture`
		of the fracture has to be specified in any case and is a scalar.

		### Isotropic hydraulic aperture with projection

		If `hydraulic aperture` is a single float, an isotropic aperture is imposed.

			"configuration": "uniform",
			"mechanical aperture: 1.0,
			"hydraulic aperture": 0.1

		This results in an element-wise computation of the unit normal and subsequent rotation of the hydraulic aperture tensor, which 
		is an expensive operation.
	

		### Full tensor hydraulic aperture

		In this case, `hydraulic aperture` is a list containing `[K_xx, K_xy, K_xz, K_yx, K_yy, K_yz, K_zx, K_zy, K_zz]` in order, with respect to global coordinates.
		Likewise, since the tensor is rotated, permeability (ah^2/12 tensor rotated) and conductivity (ah^3/12 tensor rotated) have to be specified.

			"configuration": "uniform",
			"mechanical aperture: 1.0,
			"hydraulic aperture": [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11],
			"permeability": [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11],
			"transmissivity": [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]

		It is important to note that this direct transfer to fracture hydraulic aperture means that all freacture elements
		are of identical orientation. Also, the user has to take care that the transformation results in the fracture normal
		aperture to be zero.

		## Regional uniform

		Configures homogeneous fractures for the separate regions. Requires the configuration to be set to

			"configuration": "regional uniform"

		with a list of region names and mechanical apertures (consistent order):

			"fracture regions": ["FRACTURE1", "FRACTURE2"],
			"mechanical aperture": [1.0, 2.0]

		### Isotropic hydraulic aperture with projection

		If `hydraulic aperture` is a single float per region, an isotropic aperture is imposed.

			"configuration": "regional uniform",
			"fracture regions": ["FRACTURE1", "FRACTURE2"],
			"mechanical aperture": [1.0, 2.0],
			"hydraulic aperture": [0.1, 0.2]

		This results in an element-wise computation of the unit normal and subsequent rotation of the hydraulic aperture tensor, which
		is an expensive operation.

		### Full tensor hydraulic aperture

		In this case, `hydraulic aperture` is a list containing `[K_xx, K_xy, K_xz, K_yx, K_yy, K_yz, K_zx, K_zy, K_zz]` in order, with respect to global coordinates, 
		for each fracture region. Likewise, becuase the tensor is possibly rotated, permeability (rotated ah^2/12 tensor) and conductivity (rotated ah^3/12 tensor) have to be specified:

			"configuration": "regional uniform"
			"fracture regions": ["FRACTURE1", "FRACTURE2"],
			"mechanical aperture": [1.0, 2.0],
			"hydraulic aperture": [[9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11],
								   [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]],
			"permeabilty": [[9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11],
						    [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]],
			"conductivity": [[9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11],
						     [9.8911e-12, 7.5806e-13, 9.1479e-13, 7.5806e-13, 1.7099e-11, 1.753e-12, 9.1479e-13, 1.753e-12, 1.2423e-11]]


		The following variables are initialized by the provided configurators:

			hydraulic aperture	hy	m	3	0	1	ELEMENT
			mechanical aperture	me	m	1	0	1	ELEMENT
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT

		@todo Realistic numbers in examples
		@todo If no fractures present, no settings should be required
		*/

} // !tperm
} // !csmp

#endif // !TP_MATRIXCONFIGFACT_H