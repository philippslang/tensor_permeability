#ifndef TP_DFNOMEGA_H
#define TP_DFNOMEGA_H

#include "omega.h"


namespace csmp {
	// forwards
	template<size_t> class Element;


	namespace tperm {

		/// Sampling region container class for DFN (no matrix) models
		class DfnOmega : public Omega
		{
		public:
			DfnOmega();
			explicit DfnOmega(double tv) : tv_(tv) {};
			virtual ~DfnOmega();

			virtual double total_volume() const override { return tv_; };
			void total_volume(double tv) { tv_ = tv; };

		private:
			double tv_;
		};


		/** \class DfnOmega

		This enables total volume accessors for when the total volume is not defined by the sum of its sampling elements.
		*/


	} // !tperm
} // !csmp

#endif // !TP_DFNOMEGA_H