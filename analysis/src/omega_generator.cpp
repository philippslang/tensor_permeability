#include "omega_generator.h"

#include "omega.h"
#include "bpreds.h"

#include "Element.h"

#include <iterator>

using namespace std;

namespace csmp {
	namespace tperm {


		/**
		Computes element volume. For fracture elements, this requires the variable 

		\code
		// fracture elements
		mechanical aperture	me	m	1	0	1	ELEMENT
		\endcode
		*/
		void omega_from_elements(const vector<csmp::Element<3>*>& elmts, const csmp::Index& am_key, Omega& o)
		{
			o.resize(elmts.size());
			const bool two_d(false);
			FractureElement<3> fel(two_d);
			const auto bit = begin(o);
			for (auto it(bit); it != end(o); ++it) {
				it->ePtr = elmts.at(distance(bit, it));
				it->eVol = it->ePtr->Volume();
				if (fel(it->ePtr))
					it->eVol = it->eVol*it->ePtr->Read(am_key);
			}
		}


	} // ! tperm
} // !csmp