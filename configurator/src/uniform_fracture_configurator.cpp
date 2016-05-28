#include "uniform_fracture_configurator.h"
#include "bpreds.h"
#include "ttrans.h"
#include "elops.h"

#include "Model.h"

namespace csmp {
	namespace tperm {


		/**
		This ctor causes subsequently that all fracture elements hold the same hydraulic aperture tensor, thus need to have the same
		orientation in space. The tensor needs to reflect that the fractre normal direction aperture is zero, and that the eigenvalues
		are aligned in the fracture plane, plus the unormal.
		*/
		UniformFractureConfigurator::UniformFractureConfigurator(const csmp::TensorVariable<3>& ah, double am)
			: Configurator(), ah_(ah), am_(am), project_(false)
		{
		}


		/**
		Attention: Expensive version. Subsequently this causes for all fracture elements to have their unit normal
		evaluated. For a faster version, do the transformation manually and specify the Tensor as is for trivial fracture geometries.
		*/
		UniformFractureConfigurator::UniformFractureConfigurator(double ah, double am)
			: Configurator(), ah_(csmp::TensorVariable<3>(PLAIN, ah, 0., 0., 0., ah, 0., 0., 0., 0.)), am_(am), project_(true)
		{
		}


		/**
		Assigns uniform transmissivity to all lower-dimensional elements in `Model`. Depending on the construction, this
		either assigns the tensor as is or computes a projection.
		*/
		bool UniformFractureConfigurator::configure(Model& model) const
		{			
			auto felmts = model.ElementsFrom(FractureElement<3>(false));
			input_am(model, felmts);
			const Index ahKey(model.Database().StorageKey("hydraulic aperture"));
			if (!project_)
				for (const auto& it : felmts)
					it->Store(ahKey, ah_);
			else
				project_ah(model, felmts);
			return true;
		}


		/// Inputs mechanical aperture
		void UniformFractureConfigurator::input_am(Model& model, const std::vector<Element<3>*>& felmts) const
		{
			const Index amKey(model.Database().StorageKey("mechanical aperture"));
			const ScalarVariable am(PLAIN, am_);
			for (const auto& it : felmts)
				it->Store(amKey, am);
		}


		/// Projects (x-y) isotropic hydraulic aperture tensor, expects zero components except for ah_xx and ah_yy
		void UniformFractureConfigurator::project_ah(Model& model, const std::vector<Element<3>*>& felmts) const
		{
			const Index ahKey(model.Database().StorageKey("hydraulic aperture"));
			const TensorVariable<3> ah_loc(ah_);     // ah tensor in local coord sys
			// working variables
			array<VectorVariable<3>, 3> eloc;        // element plane unit vectors w.r.t. glob coord-system
			array<csmp::Point<3>, 3> pts;            // three points on fracture plane
			TensorVariable<3> trans_tens, ah_glob;   // transformation tensor and element aperture in global coords
			VectorVariable<3> dcosine;               // direction cosine

			for (const auto& it : felmts) {
				nd_coords(it, pts);      // get local nodes
				local_uvecs(pts, eloc);  // get local unit vecs
				trans_tensor(eloc, dcosine, trans_tens);   // transformation tensor
				trans_tensor(trans_tens, ah_loc, ah_glob); // transforming local to global ah
				it->Store(ahKey, ah_glob);                 // m
			}
		}


	} // !tperm
} // ! csmp