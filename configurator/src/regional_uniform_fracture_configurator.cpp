#include "regional_uniform_fracture_configurator.h"
#include "bpreds.h"
#include "ttrans.h"
#include "elops.h"

#include "Model.h"

#include <stdexcept>

using namespace std;

namespace csmp {
	namespace tperm {


		/**
		This ctor causes subsequently that all fracture elements hold the same hydraulic aperture tensor, thus need to have the same
		orientation in space. The tensor needs to reflect that the fractre normal direction aperture is zero, and that the eigenvalues
		are aligned in the fracture plane, plus the unormal.
		*/
		RegionalUniformFractureConfigurator::RegionalUniformFractureConfigurator(const vector<csmp::TensorVariable<3>>& ahs,
																				 const vector<double>& ams,
																				 const vector<string>& rnames)
			: UniformFractureConfigurator(csmp::TensorVariable<3>(PLAIN, 0.), 0.), ahs_(ahs), ams_(ams), frnames_(rnames)
		{
			check_vsize();
		}


		/**
		Attention: Expensive version. Subsequently this causes for all fracture elements to have their unit normal
		evaluated. For a faster version, do the transformation manually and specify the Tensor as is for trivial fracture geometries.
		*/
		RegionalUniformFractureConfigurator::RegionalUniformFractureConfigurator(const vector<double>& ahs,
																				 const vector<double>& ams,
																				 const vector<string>& rnames)
			: UniformFractureConfigurator(0., 0.), ahs_(ahs.size(), this->ah_), ams_(ams), frnames_(rnames)
		{
			for (size_t i(0); i < ahs.size(); ++i)
				ahs_[i] = csmp::TensorVariable<3>(PLAIN, ahs[i], 0., 0., 0., ahs[i], 0., 0., 0., 0.);
			check_vsize();
		}


		void RegionalUniformFractureConfigurator::check_vsize() const
		{
			if (ahs_.size() == ams_.size() == frnames_.size())
				return;
			throw runtime_error("Vectors for regional fracture configuration are not of uniform length");
		}


		/**
		Assigns uniform transmissivity to all lower-dimensional elements in `Model`. Depending on the construction, this
		either assigns the tensor as is or computes a projection. Relies on the following variables, which are set in here

			hydraulic aperture	hy	m	3	0	1	ELEMENT
			mechanical aperture	me	m	1	0	1	ELEMENT
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT

		Assumes unit viscosity.
		*/
		bool RegionalUniformFractureConfigurator::configure(Model& model) const
		{			
			for (size_t r(0); r < ahs_.size(); ++r) {
				auto felmts = model.ElementsFrom(FractureElement<3>(false), frnames_[r].c_str());
				input_am(model, felmts, ams_[r]);
				if (!this->project_)
					direct_ah(model, felmts, ahs_[r]);
				else
					project_ah(model, felmts, ahs_[r]);
			}
			return true;
		}


		


	} // !tperm
} // ! csmp