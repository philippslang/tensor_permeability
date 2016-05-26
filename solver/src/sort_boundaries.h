/** @file */
#ifndef SBOUNDARIES_H
#define SBOUNDARIES_H


#include <utility>
#include <vector>

#include "boundaries.h"


namespace csmp {
	template<size_t> class Model;

	namespace tperm {
		class Settings;

		/// Returns sorted Boundaries of the Model
		Boundaries sort_boundaries(const csmp::Model<3>&, const Settings&);
		
	} // !tperm
} // !csmp


#endif // !SBOUNDARIES_H