#include "uniform_matrix_configurator.h"
#include "bpreds.h"

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


		/**
		Assigns permeability and conductivity to all equi-dimensional elements in `Model`. Relies on the following variables:

			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT
		*/
		bool UniformMatrixConfigurator::configure(Model& model) const
		{
			auto melmts = model.ElementsFrom(MatrixElement<3>(false));
			const Index pKey(model.Database().StorageKey("permeability"));
			const Index cKey(model.Database().StorageKey("conductivity"));
			for (const auto& it : melmts) {
				it->Store(pKey, perm_);
				it->Store(cKey, perm_);
			}
			return true;
		}


	} // !tperm
} // ! csmp