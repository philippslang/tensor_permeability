#ifndef TP_REGUNIFFRACCONFIG_H
#define TP_REGUNIFFRACCONFIG_H

#include "uniform_fracture_configurator.h"


namespace csmp {
	template<size_t> class Element;

	namespace tperm {

		/// Configures uniform fractures, on a by region basis
		class RegionalUniformFractureConfigurator : public UniformFractureConfigurator
		{
		public:
			RegionalUniformFractureConfigurator() = delete;
			/// Allowing for full tensor to be specified
			RegionalUniformFractureConfigurator(const std::vector<csmp::TensorVariable<3>>& ahs,
												const std::vector<csmp::TensorVariable<3>>& ks, 
												const std::vector<csmp::TensorVariable<3>>& cs,
												const std::vector<double>& ams,
												const std::vector<std::string>& rnames);
			/// Spherical tensor, i.e. isotropic transmissivity
			RegionalUniformFractureConfigurator(const std::vector<double>& ahs,
												const std::vector<double>& ams,
												const std::vector<std::string>& rnames);

			virtual bool configure(Model&) const;

		private:
			void check_vsize() const;			
			const std::vector<double> ams_;
			const std::vector<std::string> frnames_;
			std::vector<csmp::TensorVariable<3>> ahs_, ks_, cs_;
		};

		/** \class RegionalUniformFractureConfigurator

		Configures (3D model) equidimensional elements to a uniform `hydraulic aperture` and `mechanical aperture` and corresponding
		`conductivity` (m3/Pa.s) and `permeability` (m2) Depending on the chosen ctor, either a provided tensor will be assigned to all,
		or an isotropic hydraulic aperture will be  assigned by projecting the appropriate tensor. The latter requires and element-wise 
		computation of the unit normal. This is expensive. 
		
		The provided vectors for the ctors are of identical size and correspond to each region to be
		initialized. It is the users responsability to include all fratcure regions, so that no uninitialized parts of the model
		remain for subsequent pressure solutions.

		The following variables are initialized by the provided configurators:

			hydraulic aperture	hy	m	3	0	1	ELEMENT
			mechanical aperture	me	m	1	0	1	ELEMENT
			conductivity	co	m2 Pa-1 s-1	3	1e-25	1	ELEMENT
			permeability	pe	m2	3	1e-25	1e-08	ELEMENT
		*/

	} // !tperm
} // !csmp

#endif // !TP_REGUNIFFRACCONFIG_H