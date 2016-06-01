#include "omega_bdistance_configurator.h"

#include "Model.h"

namespace csmp {
	namespace tperm {


		OmegaBDistanceConfigurator::OmegaBDistanceConfigurator()
			: Configurator(), dist_(0.)
		{
		}


		OmegaBDistanceConfigurator::OmegaBDistanceConfigurator(double dist)
			: Configurator(), dist_(dist)
		{
		}


		/**
		This is based on a nearest node criterion to all boundaries.

		@todo Improve efficiency. In most cases, we should be able to specify boundaries as planes
		@todo Somewhat dependent on the resolution of the model boundary
		*/
		bool OmegaBDistanceConfigurator::configure(Model& m) const
		{
			Point<3> ebc;
			m.UpdateIndices();
			vector<size_t> omega_ids;
			omega_ids.reserve(m.Region("Model").Elements());
			for (const auto& eit : m.Region("Model").ElementVector())
			{
				ebc = eit->BaryCenter();
				double dmin = numeric_limits<double>::max();
				for (Model::boundaryIterator bit = m.BoundariesBegin(); bit != m.BoundariesEnd(); ++bit)
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
					omega_ids.push_back(eit->Idx());
			}
			if (omega_ids.size()) {
				m.FormRegionFrom("omega", omega_ids);
				return true;
			}
			return false;
		}


	} // !tperm
} // ! csmp