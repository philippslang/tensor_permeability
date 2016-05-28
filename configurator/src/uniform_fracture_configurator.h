#ifndef TP_UNIFFRACCONFIG_H
#define TP_UNIFFRACCONFIG_H

#include "configurator.h"
#include "TensorVariable.h"
#include <vector>

namespace csmp {
	template<size_t> class Element;

	namespace tperm {

		/// Configures uniform fractures
		class UniformFractureConfigurator : public Configurator
		{
		public:
			UniformFractureConfigurator() = delete;
			/// Allowing for full tensor to be specified
			UniformFractureConfigurator(const csmp::TensorVariable<3>&, double);
			/// Spherical tensor, i.e. isotropic transmissivity
			UniformFractureConfigurator(double, double);

			virtual bool configure(Model&) const;

		private:
			
			void input_am(Model&, const std::vector<Element<3>*>&) const;
			void project_ah(Model&, const std::vector<Element<3>*>&) const;

			const bool project_; ///< Hydraulic aperture is isotropic (only ah_xx and ah_yy set) and needs projection
			const double am_;
			const csmp::TensorVariable<3> ah_;
		};

		/** \class UniformFractureConfigurator

		Configures (3D model) equidimensional elements to a uniform `hydraulic aperture` and `mechanical aperture`. Depending on the chosen
		ctor, either a provided tensor will be assigned to all, or an isotropic hydraulic aperture will be  assigned by projecting
		the appropriate tensor. The latter requires and element-wise computation of the unit normal. This is expensive.
		*/

	} // !tperm
} // !csmp

#endif // !TP_UNIFFRACCONFIG_H