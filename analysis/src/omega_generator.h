/** @file */
#ifndef TP_OMEGAGENERATOR_H
#define TP_OMEGAGENERATOR_H

#include <vector>
#include <memory>
#include <array> 

#include "Point.h"

namespace csmp {
	// forwards
	struct Index;
	template<size_t> class Model;
	template<size_t> class Element;


	namespace tperm {
		class Omega;

		/// ABC for omega generators
		class OmegaGenerator
		{
		public:
			using OmegaPtrColl = std::vector<std::shared_ptr<Omega>>;

			OmegaGenerator() {};
			virtual ~OmegaGenerator() {};

			virtual OmegaPtrColl generate(const csmp::Model<3>&) const = 0;	

		protected:
			/// Returns points with all minimum components and all maximum components of the provided points
			std::array<csmp::Point<3>, 2> min_max(const std::array<csmp::Point<3>, 2>& cpts) const
			{
				csmp::Point<3> min, max;
				for (size_t i(0); i < 3; ++i) {
					min[i] = cpts[0][i] < cpts[1][i] ? cpts[0][i] : cpts[1][i];
					max[i] = cpts[0][i] > cpts[1][i] ? cpts[0][i] : cpts[1][i];
				}
				return{ min, max };
			}

			/// Volume of the bounding box
			double total_volume(const std::array<csmp::Point<3>, 2>&) const;
		};

		/** \class OmegaGenerator

		Abstract base class for omega generators. Errors should be detected during ctors, and not during the generate call.

		@todo New generators should implement boost.Geometry
		*/

		/// Instantiates element pointers and volumes
		Omega omega_from_elements(const std::vector<Element<3>*>&, const csmp::Index&);


	} // !tperm
} // !csmp

#endif // !TP_OMEGAGENERATOR_H