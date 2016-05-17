#include "uniform_matrix_configurator.h"

namespace csmp {
	namespace tperm {

		UniformMatrixConfigurator::UniformMatrixConfigurator(Model& model)
			: Configurator(model)
		{
		}


		bool UniformMatrixConfigurator::configure() const
		{
			return true;
		}


	} // !tperm
} // ! csmp