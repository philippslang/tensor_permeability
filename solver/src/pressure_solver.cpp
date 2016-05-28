#include "solver.h"
#include "boundaries.h"
#include "bpreds.h"

#include "Model.h"
#include "SAMG_Solver.h"
#include "SAMG_Settings.h"
#include "PDE_Integrator.h"
#include "NumIntegral_dNT_op_dN_dV.h"
#include "NumIntegral_NT_op_N_dV.h"

using namespace std;

namespace csmp {
	namespace tperm{
		

		/**
		Relies on the following variables:

			\code
			// porperly set
			// fractures only (user)
			hydraulic aperture	hy	m	3	0	1	ELEMENT
			mechanical aperture	me	m	1	0	1	ELEMENT
			// matrix only (user)
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT
			// result, exist but must not be initialized, will contain results after exit
			// will be [m2 / Pa.s] for matrix and [m3 / Pa.s] for fractures
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			\endcode

		Viscosity is assumed unity. It follows that stored conductivity is equal to permeability for matrix,
		and equal to transmissivity for fractures.
		*/
		void conductivity(Model<3>& m)
		{
			const bool twod = containsVolumeElements(m.Region("Model"));
			const Index kKey(m.Database().StorageKey("conductivity"));
			const Index ahKey(m.Database().StorageKey("hydraulic aperture"));
			const Index pKey(m.Database().StorageKey("permeability"));
			MatrixElement<3> mbp(twod);
			TensorVariable<3> ttemp(PLAIN, 0.);
			// reset first
			m.Region("Model").InputPropertyValue("conductivity", ttemp);
			// set
			for (auto& ePtr : m.Region("Model").ElementVector()) {
				if (mbp(ePtr)) { // matrix
					ePtr->Read(pKey, ttemp);
				} else { // fracture
					ePtr->Read(ahKey, ttemp);
					ttemp.Power(3);
					ttemp = ttemp / 12.;
				}
				ePtr->Store(kKey, ttemp);
			}
		}


		/**
		Relies on the following variables:

			\code
			// initialized properly (m2 / Pa.s for matrix, m3 / Pa.s for fractures)
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			// working, exist but must not be initialized
			fluid pressure	fl	Pa	1	-1e-05	1e+09	NODE
			fluid volume source	fl	m3 s-1	1	-1	1	ELEMENT
			// result, exist but must not be initialized, will contain results after exit
			// for 0..(dimension - 1), or (number of boundaries - 1)
			pressure gradient 0	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
			velocity 0	ve	m s-1	2	-100	100	ELEMENT
			\endcode

		@todo Check that flag override when resetting actually works
		@todo Linear boundary conditions
		*/
		void solve(const Boundaries& bds, Model<3>& m)
		{
			const VectorVariable<3> zero_vec(PLAIN, 0.);
			const Parameter fp = m.Database().Parameter("fluid pressure");
			// reset fluid volume source
			m.Region("Model").InputPropertyValue("fluid volume source", makeScalar(PLAIN, 0.));
			// for each boundary set
			for (size_t d(0); d < bds.size(); ++d) {
				// reset fluid pressure, vels and pgrads
				auto rvnames = { (string) "pressure gradient " + to_string(d), (string) "velocity " + to_string(d) };
				m.Region("Model").InputPropertyValue(fp.name.c_str(), makeScalar(PLAIN, 0.));
				for (const auto& rv : rvnames)
					m.Region("Model").InputPropertyValue(rv.c_str(), zero_vec);
				// apply BCs
				dirichlet_scalar_bc(bds[d].first, fp.key, 1.0);
				dirichlet_scalar_bc(bds[d].second, fp.key, -1.0);
				// solve pressure
				// compute pressure gradient
				// compute velocity
				// store results
			}
		}


		void dirichlet_scalar_bc(const tperm::Boundary& bd, const Index& k, double val)
		{
			const ScalarVariable bval(DIRICH, val);
			for (size_t i(0); i < bd.size(); ++i)
				bd[i]->Store(k, bval);
		}


		/**
		Relies on the following variables:

			\code
			// initialized properly (m2 / Pa.s for matrix, m3 / Pa.s for fractures)
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			// initialized to proper values (fvs) and boundary conditions (fp)
			// result is contained in (fp)
			fluid pressure	fl	Pa	1	-1e-05	1e+09	NODE
			fluid volume source	fl	m3 s-1	1	-1	1	ELEMENT
			\endcode

		@todo Alternative small budget solver
		*/
		void solve_pressure(csmp::Model<3>& m)
		{
			SAMG_Settings samg_settings;
			SAMG_Solver samg_solver(&samg_settings);			

			PDE_Integrator<3, Region> ssfp((csmp::Solver*) &samg_solver);
			// conductance matrix [K] on the left-hand side
			NumIntegral_dNT_op_dN_dV<3> conductance(m.Database(), "conductivity", "fluid pressure", "fluid pressure");
			// source vector {Q} on the right-hand side
			NumIntegral_NT_op_N_dV<3> source(m.Database(), "fluid volume source", "fluid pressure");
			// add PDE_Operators to the FE Algorithm
			ssfp.Add(&conductance);
			ssfp.Add(&source);
			m.Apply(ssfp);
		}


	} // !tperm
} // !csmp