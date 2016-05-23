# Tensor Permeability {#mainpage}

Tensor permeability is a C++ finite element (FE) framework and executable for the comutation of the full upscaled permeability 
tensor in porous media. It is based upon CSMP++ finite element data structures and algorithms. The main features
of tensor permeabilty are:

- Upscaling of the full permeability tensor for arbitrary geometries in porous media
	
	+ No assumptions are made on the orientation of upscaled pemability eigenvalues
	+ No peridcicity requirements are made as to the underlying geometry and permeability distribution
	+ Emphasis on fractur support
	
- Incorporation of locally varying and tensor-form permeability and transmissivity

	+ Matrix permeability and
	+ Fracture transmissivity can be input as full tensors (element-wise constant)
	
- Highly tested against analytical solutions

	+ Numerous benchmark, with emphasis on discrete fracture and matrix models (DFMs) 
	
- `JSON` based application I/O, C++ API and Python interface.

	+ Standardized file interfaces for application control and output
	+ C++ and Python API for seamless integration
