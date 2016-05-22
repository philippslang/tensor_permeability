#include "uniform_matrix_configurator.h"
#include "Model.h"

namespace csmp {
	namespace tperm {


		UniformMatrixConfigurator::UniformMatrixConfigurator(const csmp::TensorVariable<3>& perm)
			: Configurator(), perm_(perm)
		{
		}


		UniformMatrixConfigurator::UniformMatrixConfigurator(double perm)
			: Configurator(), perm_(csmp::TensorVariable<3>(PLAIN, perm, 0., 0., 0., perm, 0., 0., 0., perm))
		{
		}


		bool UniformMatrixConfigurator::configure(Model& model) const
		{
			const char* vname = "permeability";
			Region<3>& mref = model.Region("MATRIX");
			if (model.Database().Type(vname) == SCALAR)
				mref.InputPropertyValue(vname, makeScalar(PLAIN, perm_.Trace()/3.0));
			else 
				mref.InputPropertyValue("permeability", perm_);
			return true;
		}


	} // !tperm
} // ! csmp