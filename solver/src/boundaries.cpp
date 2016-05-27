#include "boundaries.h"

namespace csmp {
	namespace tperm{


		Boundary::Boundary()
			: nodes_()
		{
		}


		/// Initializes three empty Boundary pairs
		Boundaries::Boundaries()
			: boundaries_(3)
		{
		}


	} // !tperm
} // !csmp