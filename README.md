# Tensor Permeability {#mainpage}

Tensor permeability is a C++ finite element (FE) framework and executable for the comutation of the full upscaled permeability 
tensor in porous media. It is based upon CSMP++ finite element data structures and algorithms. The main features
of tensor permeabilty are:

- Upscaling of the full permeability tensor for arbitrary geometries in porous media, often fractured
	
	+ No assumptions are made on the orientation of upscaled pemability eigenvalues
	+ No peridcicity requirements are made as to the underlying geometry and permeability distribution
	
- Incorporation of locally varying and tensor-form permeability and transmissivity

	+ Matrix permeability and fracture transmissivity can be input as full tensors (element-wise constant)
	
- Highly tested against analytical solutions

	+ Numerous benchmark DFMs 
	
- `JSON` based application I/O.

	+ Standardized file interfaces for application settings and results.
