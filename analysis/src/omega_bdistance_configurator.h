#ifndef TP_OMEGABDCONFIG_H
#define TP_OMEGABDCONFIG_H

#include "configurator.h"
#include <string>
#include <array>
#include <algorithm> 

namespace csmp {

	namespace tperm {

		/// Creates sampling region using a boundary distance criterion
		class OmegaBDistanceConfigurator : public Configurator
		{
		public:
			/// All elements
			explicit OmegaBDistanceConfigurator();
			/// All with distance from model boundaries
			explicit OmegaBDistanceConfigurator(double);

			virtual bool configure(Model&) const;

		private:
			const double dist_;
		};


		/** \class OmegaBDistanceConfigurator

		Creates non-unique csmp::Region `omega` that contains all csmp::Element within certain distance
		of all outer model boundaries.
		*/


		/// Identification of outer model boundary based on naming convention
		inline bool is_main_boundary_id(std::string blname)
		{
			static const std::array<std::string, 12> outer = { "TOP", "BOTTOM", "LEFT", "RIGHT", "FRONT", "BACK" , 
				"BOUNDARY1", "BOUNDARY2", "BOUNDARY3", "BOUNDARY4", "BOUNDARY5", "BOUNDARY6"};
			auto it = find(outer.begin(), outer.end(), blname);
			if (it != outer.end())
				return true;
			return false;
		}

	} // !tperm
} // !csmp

#endif // !TP_OMEGABDCONFIG_H