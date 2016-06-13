#include "omega.h"

#include <algorithm>
#include <numeric>

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
			return accumulate(cbegin(), cend(), 0., [](const double v, const auto& einf) { return v+einf.eVol; });;
		}


	} // ! tperm
} // !csmp