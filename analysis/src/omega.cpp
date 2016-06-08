#include "omega.h"

#include <algorithm>

using namespace std;

namespace csmp {
	namespace tperm {

		Omega::Omega()
			: eInfos_()
		{
		}

		Omega::~Omega()
		{
		}

		double Omega::total_volume() const
		{
			double v(0.);
			for_each(cbegin(), cend(), [&v](const auto& einf) { v += einf.eVol; });
			return v;
		}


	} // ! tperm
} // !csmp