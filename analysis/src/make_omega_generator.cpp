#include "make_omega_generator.h"
#include "omega_generator.h"
#include "settings.h"
#include "omega_bdistance_generator.h"
#include "omega_corner_points_generator.h"
#include "Model.h"

using namespace std;

namespace csmp {
	namespace tperm{


		/**
		Returns nullptr if settings incorrect.
		*/
		std::unique_ptr<OmegaGenerator> make_omega_generator(const Settings& s)
		{
			std::unique_ptr<OmegaGenerator> uPtr(nullptr);
			const string c = s.json["configuration"].get<string>();

			if (c == (string)"uniform boundary distance") {
				const double dist = s.json["distance"].get<double>();
				uPtr.reset(new OmegaBDistanceGenerator(dist));
			}
			else if (c == (string)"bounding box") {
				auto boxes = s.json["corner points"].get<vector<vector<vector<double>>>>();
				vector<array<csmp::Point<3>, 2>> omega_bcoords;
				for (size_t o(0); o < boxes.size(); ++o)
					omega_bcoords.push_back({ csmp::Point<3>(boxes.at(o).at(0).at(0), boxes.at(o).at(0).at(1), boxes.at(o).at(0).at(2)),
						csmp::Point<3>(boxes.at(o).at(1).at(0), boxes.at(o).at(1).at(1), boxes.at(o).at(1).at(2)) });
				uPtr.reset(new OmegaCornerPointsGenerator(omega_bcoords));
			}
			return uPtr;
		}

	} // !tperm
} // !csmp