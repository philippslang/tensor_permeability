# GoFrak project 

This walk-through is specific to the GoFrak comparison project 2016, and is not a comprehensive manual of
the tool. It explains the subset of features that are used for this project using an example geometry.

## Before you start

Prerequisites to run tensor permeability are:

- The binaries `tensor_permeability.exe`, `libamg_dyn.dll`, and `libiomp5md.dll` must be present
- MSVC [runtime](https://www.microsoft.com/en-us/download/details.aspx?id=48145) must be installed
- Environment variable `LM_LICENSE_FILE = @ese-darcy.ese.ic.ac.uk` for SAMG licencse; college network access

Optional for permeability ellipsoid plotting

- Anaconda [Python 3.5](https://docs.continuum.io/anaconda/install#anaconda-for-windows-install)
- Ellipsoid [script from GitHub](https://github.com/plang85/tensor_permeability/blob/master/python/tp_ellipsoid.py)

## The Model

A `Model` in  our framework refers to a finite-element mesh that captures some geometry, in this case a fracture
network. A `Model` can have an infinite number of `Configurations`, which refer to the material properties
that are assigned to different parts of the model. For a GoFrak input file like `sim_Dfn_sim_ex1.txt` this

		data-set	fset_id	fracture-shape	x_center	y_center	z_center...
		Dfn_sim_BCF3a_0	0	rectangle	33.25267791748	1.592755317688	11.38181686401	...
		Dfn_sim_BCF3a_0	0	rectangle	37.56771850586	71.92542266846	11.38181686401	...
		Dfn_sim_BCF3a_0	0	rectangle	99.81115722656	44.06266021729	11.38181686401	...
		...
		Dfn_sim_BCF2a_0	5	rectangle	0.3895772099495	19.9815120697	5.927612304688	...
		Dfn_sim_BCF2a_0	5	rectangle	36.18391418457	46.50354003906	4.707766532898	...
		Dfn_sim_BCF2a_0	5	rectangle	92.78861236572	27.25434684753	5.556463241577	...

a FE model with two files (`sim_Dfn_sim_ex1.asc` and `sim_Dfn_sim_ex1.dat`) is created. In this (geometrical) model, the fracture sets `BCF3a` ... `BCF2a` exist. 
When configuring the model, apertures can be assigned on a fracture set-basis using these names. You can check the names for the
fracture sets in the provided `.asc` file, which should look something like this

	XXX
	
## Settings

To run a simulation, a `Configuration` is needed to complement the `Model`. This configuration describes
what fracture apertures are used for what fracture sets. Additionally, we need to specify some runtime
parameters as to the computation of the effective permeability tensor, e.g. for which subregions to upscale
permeability. We will use a basic settings file that contains both configuration and runtime parameters. This
file won't change in structure for any of the proposed runs, and we'll highlight the modifiable stuff later. The file
`settings.json` looks like this

		{
			"model":{
				"file name": "sim_Dfn_sim_ex1",
				"format": "icem"
				},
			"configuration":{
				"matrix":{
					"configuration": "uniform",
					"permeability": 1.0E-15	
				},
				"fractures":{
					"configuration": "regional uniform",
					"fracture regions": ["BCF1A","BCF2A","BCF3B"],
					"mechanical aperture": [0.01,0.015,0.2],
					"hydraulic aperture": [0.005,0.01,0.15]
				}
			},
			"analysis":{
				"configuration": "bounding box",
				"corner points": [[[30.0,30.0,2.0],[50.0,50.0,8.0]],[[45.0,45.0,6.0],[70.0,70.0,10.0]]]
			},
			"output":{
				"results file name": "results.json",
				"vtu": true,
				"vtu regions": ["BCF1A","BCF2A","BCF3B"]
			}
		}

The file contains four sections

- `model`
	+ Indicates which model to run and what regions to load. This should't change, and be used as it comes with the provided model files
- `configuration`
	+ This contains the material propeties of the fractures and the matrx. The matrix subsetcion shouldn't change, and the fracture
	  section will be described below
- `analysis`
	+ Describes the subregions over which permeability will be upscaled. The format will be discussed below.
- `output`
	+ Describes what to output as text and as visualization. Shouldn't change, except when the amount of files produced becomes an issue.

### Adjusting the model configuration

The settings section `configuration` contains a matrix and a fracture subsection. The fracture subsection sets
the mechanical and hydraulic aperture for each fracture set, in the order they are provided under `fracture regions`. It is likely
that `fracture regions` and `"configuration": "regional uniform"` never change, and only the values will be adapted:

			"mechanical aperture": [0.01,0.015,0.2],
			"hydraulic aperture": [0.005,0.01,0.15]

these lists contain the values for each set in the order as provided in `fracture regions` and are in unit meters. 

### Adjusting the upscaling regions

The upscaling regions are boxes aligned with the global xyz coordinate system and specified by a pair of opposing
corner points. For two sampling regions

		"configuration": "bounding box",
		"corner points": [[[30.0,30.0,2.0],[50.0,50.0,8.0]],[[45.0,45.0,6.0],[70.0,70.0,10.0]]]

## Running

The `.asc`, `.dat` and `.json` files need to be in the working directory. Then we use a local batch file
to call 

		tensor_permeability.exe

if the settings file is called `settings.json`, or 

		tensor_permeability.exe settings1.json

if it is called `settings1.json` for example. For multiple settings files in the same directory, don't forget to change
the output filename in the `analysis` settings section to, for example

		"results file name": "results1.json"

else previous results may be overwritten.

## Analysis

The full tensor, eigenvectors and eigenvalues will be output to the file specified in `results file name`, and might look like this

		XXX

Also, each fracture set, each upscaling region (`omega`) and the entire model will be output to vtu, which may be used to
produce a plot like this

		XXX

Optionally, the upscaled permeability tensor can be visualized using the python script `tp_ellipsoid.py`. This should
also be done by means of a local batch file to call

		python tp_ellipsoid.py

if the results filename is `results.json` or

		python tp_ellipsoid.py results1.json

for other filenames. This requires Python 3.5 in PATH, and produces an interactive window per sampling region
that can be rotated and saved as a bitmap.

		XXX