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


# Running as an executable

## The `JSON` settings file

A minimal configuration looks like this:

		{
			"model":{
				"file name": "debug",
				"format": "icem"
			},
			"configuration": {
				"matrix":{
					"configuration": "uniform",
					"permeability": 1.0E-15
				},
					"fractures":{
						"configuration": "uniform",
						"mechanical aperture": 0.0001, 
						"hydraulic aperture": 0.0001
				}
			},
			"analysis":{
				"configuration": "uniform boundary distance",
				"distance": 2.0
			}
		}

This JSON object has three required subsections: `model`, `configuration` and `analysis`. We're going to look at the model
section first

### Loading a model

The mininal `model` object loads a model from disk using a file name

		"file name": "debug",
		"format": "icem" # supports: "icem" and "csmp binary"

For the `csmp binary` option, the model is loaded as a whole, assuming `debug.asc` and `debug.dat` present, the latter in binary mode.
For the `icem` option, the model is loaded with all Ansys Icem families as csmp::Region, or csmp::Boundary. 
An optional argument specifies a regions file to be used for the `"format": "icem"` case:

		"regions file": "debug_r1"

In this case, the file `debug_r1-regions.txt` is assumed to be present in the woking directory and loaded as csmp regions file.
As a second option, a regions file can be generated for all regions specified in the configuration:

		"regions": ["FRACTURES", "MATRIX"]

This creates a temporary regions file that is being used when loading the Ansys model.
