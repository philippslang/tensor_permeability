#include "uniform_matrix_configurator.h"

namespace csmp {
	namespace tperm {

		UniformMatrixConfigurator::UniformMatrixConfigurator(const csmp::TensorVariable<3>& perm)
			: Configurator(), perm_(perm)
		{
		}


		bool UniformMatrixConfigurator::configure(Model& model) const
		{
			return true;
		}


	} // !tperm
} // ! csmp