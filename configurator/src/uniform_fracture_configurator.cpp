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
		either assigns the tensor as is or computes a projection. Relies on the following variables, which are set in here

			hydraulic aperture	hy	m	3	0	1	ELEMENT
			mechanical aperture	me	m	1	0	1	ELEMENT
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT

		Assumes unit viscosity.
		*/
		bool UniformFractureConfigurator::configure(Model& model) const
		{			
			auto felmts = model.ElementsFrom(FractureElement<3>(false));
			input_am(model, felmts, am_);
			const Index ahKey(model.Database().StorageKey("hydraulic aperture"));
			const Index kKey(model.Database().StorageKey("permeability"));
			const Index cKey(model.Database().StorageKey("conductivity"));
			
			if (!project_) {
				TensorVariable<3> k(ah_), c(ah_);
				k.Power(2.); k /= 12.;
				c.Power(3.); c /= 12.;
				for (const auto& it : felmts) {
					it->Store(ahKey, ah_);
					it->Store(kKey, k);
					it->Store(cKey, c);
				}
			}
			else
				project_ah(model, felmts, ah_);
			return true;
		}


		/// Inputs mechanical aperture
		void UniformFractureConfigurator::input_am(Model& model, const std::vector<Element<3>*>& felmts, double a) const
		{
			const Index amKey(model.Database().StorageKey("mechanical aperture"));
			const ScalarVariable am(PLAIN, a);
			for (const auto& it : felmts)
				it->Store(amKey, am);				
		}


		/// Projects (x-y) isotropic hydraulic aperture tensor, expects zero components except for ah_xx and ah_yy
		void UniformFractureConfigurator::project_ah(Model& model, const std::vector<Element<3>*>& felmts, const csmp::TensorVariable<3>& ah) const
		{
			const array<Index, 3> keys = { Index(model.Database().StorageKey("hydraulic aperture")), 
										   Index(model.Database().StorageKey("permeability")), 
									       Index(model.Database().StorageKey("conductivity")) };
			// corresponding to indices in keys
			array<TensorVariable<3>, 3> ts_loc = { TensorVariable<3>(ah), TensorVariable<3>(ah), TensorVariable<3>(ah) };
			ts_loc[1].Power(2.); ts_loc[1] /= 12.; // m2
			ts_loc[2].Power(3.); ts_loc[2] /= 12.; // m3 / Pa.s
			// working variables
			array<VectorVariable<3>, 3> eloc;        // element plane unit vectors w.r.t. glob coord-system
			array<csmp::Point<3>, 3> pts;            // three points on fracture plane
			TensorVariable<3> trans_tens(PLAIN, 0.), // transformation tensor
							  t_glob(PLAIN, 0.);     // and element prop in global coords
			VectorVariable<3> dcosine;               // direction cosine 
			// rotate and store
			for (const auto& it : felmts) {
				nd_coords(it, pts);                       // get local nodes
				local_uvecs(pts, eloc);                   // get local unit vecs
				trans_tensor(eloc, dcosine, trans_tens);  // transformation tensor
				for (size_t i(0); i < keys.size(); ++i) {					
					rot_tensor(trans_tens, ts_loc[i], t_glob);  // transforming local to global
					it->Store(keys[i], t_glob);                 // store
				}
			}
		}


	} // !tperm
} // ! csmp