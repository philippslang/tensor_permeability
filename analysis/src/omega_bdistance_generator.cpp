#include "omega_bdistance_generator.h"
#include "omega.h"
#include "model_io.h"

#include "Point.h"
#include "Model.h"

using namespace std;

namespace csmp {
	namespace tperm {

		OmegaBDistanceGenerator::OmegaBDistanceGenerator()
			: dist_(0.)
		{}

		OmegaBDistanceGenerator::OmegaBDistanceGenerator(double dist)
			: dist_(dist)
		{}

		OmegaBDistanceGenerator::~OmegaBDistanceGenerator()
		{}

		OmegaBDistanceGenerator::OmegaPtrColl OmegaBDistanceGenerator::generate(const csmp::Model<3>& m) const
		{
			OmegaPtrColl ptrs(1, make_shared<Omega>());
			const Index am_key(m.Database().StorageKey("mechanical aperture"));

			csmp::Point<3> ebc;
			vector<csmp::Element<3>*> ePtrs;
			ePtrs.reserve(m.Region("Model").Elements());
			for (const auto& eit : m.Region("Model").ElementVector())
			{
				ebc = eit->BaryCenter();
				double dmin = numeric_limits<double>::max();
				for (auto bit = m.BoundariesBegin(); bit != m.BoundariesEnd(); ++bit)
				{
					if (!is_main_boundary_id(bit->first.second))
						continue;
					for (const auto& bnit : bit->second.NodeVector())
					{
						double const dist = ebc.DistanceTo(bnit->Coordinate());
						if (dist < dmin)
							dmin = dist;
					}
				}
				if (dmin >= dist_)
					ePtrs.push_back(eit);
			}
			omega_from_elements(ePtrs, am_key, *ptrs[0]);
			return ptrs;
		}

	} // ! tperm
} // !csmp