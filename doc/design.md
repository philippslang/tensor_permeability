# Design

So far only 3D implemented. 2D requires: only scalars for k, K etc... and corresponding factories. Evaluation should stay universal.

tperm::Settings restricted to tperm::ConfiguratorFactory and flow part, individual tperm::Configurator independent

Permeability is a csmp tensor variable

The results of each pressure run are stored in `pressure gradient 0` and `velocity 0` for 0-1 (2D) or 0-2 (3D)

Pervasive assumptions throughout the application are

- Pressure is solved over the entier `Model` region
- Viscosity is unity
- Boundary naming conventions are, as opposing pairs, `BOUNDARY1` and `BOUNDARY2`, or `TOP` and `BOTTOM` , etc... Internally, they are only used in terms of their nodes, so they could be regions (internal) too
- Matrix elements are equi-dimensional and fracture elements are lower dimensional
- Upscaled permeability is obtained for all (non-unique) regions in the model with names starting with `omega`
- The variables that exist throughout the lifetime of the Model are (3D)
		
		// fluid pressure solver (internal)
		conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT # m3/Pa.s for lo-dims, m2/Pa.s for eq-dim
		fluid pressure	fl	Pa	1	-1e-05	1e+09	NODE
		fluid volume source	fl	m3 s-1	1	-1	1	ELEMENT
		// fractures only (user)
		hydraulic aperture	hy	m	3	0	1	ELEMENT
		mechanical aperture	me	m	1	0	1	ELEMENT
		// matrix and fractures
		permeability	pe	m2	3	1e-25	1e-08	ELEMENT
		// results (internal)
		pressure gradient 0	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
		pressure gradient 1	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
		pressure gradient 2	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
		velocity 0	ve	m s-1	2	-100	100	ELEMENT
		velocity 1	ve	m s-1	2	-100	100	ELEMENT
		velocity 2	ve	m s-1	2	-100	100	ELEMENT

The variables `hydraulic aperture` and `mechanical aperture` are only initialized over the fractures

The tensor `hydraulic aperture` has to honour that the fracture normal eigenvector corresponding eigenvalue is zero

The variable `permeability` is only initialized for the matrix of the model

@todo Check that tensor trans is ok
@todo consolidate 2D criterion to function
@todo need an exception and log policy
@todo 2D support, highlight whats not ready with todos
@todo Internal boundaries, means regions. requires a keyword to set elements cond to zero and not include in fracs output