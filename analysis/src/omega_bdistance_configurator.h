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
			OmegaBDistanceConfigurator();
			/// All with distance from model boundaries
			explicit OmegaBDistanceConfigurator(double);

			virtual bool configure(Model&) const override;

		private:
			const double dist_;
		};


		/** \class OmegaBDistanceConfigurator

		Creates non-unique csmp::Region `omega` that contains all csmp::Element within certain distance
		of all outer model boundaries.

		@deprecated We don't use omega configurators - look for the equivalent function factory
		*/


	} // !tperm
} // !csmp

#endif // !TP_OMEGABDCONFIG_H