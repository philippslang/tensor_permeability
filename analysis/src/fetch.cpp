#include "fetch.h"
#include "Model.h"
#include "results.h"
#include "bpreds.h"
#include "analyze.h"

#include <cmath>

using namespace std;

namespace csmp {
	namespace tperm{


		map<string, UpscaledTensor> fetch(const csmp::Model<3>& m, const char* rtag)
		{
			map<string, UpscaledTensor> r;
			const size_t md = containsVolumeElements(m.Region("Model")) ? 3 : 2;
			for (auto rit = m.RegionsBegin(); rit != m.RegionsEnd(); ++rit)
			{
				// is sampling region
				if (rit->first.find(rtag) == -1)
					continue;
				vector<FlowResults> fr;
				for (size_t d(0); d < md; ++d)
					fr.push_back(fetch(d, rit->first.c_str(), m));
				auto ri = analyze(fr);
				r.insert(std::make_pair(rit->first, ri));
			}
			return r;
		}
		

		/**
		Fetches tperm::FlowResults for experiment `d` and given region. Element volumes are the finite element volumes for matrix elements,
		and the finite element area times the `mechanical aperture` for fracture elements.

		Relies on the following variables:

		\code
		// fracture elements
		mechanical aperture	me	m	1	0	1	ELEMENT
		// vector variables, for provided dimension d
		pressure gradient 0	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
		velocity 0	ve	m s-1	2	-100	100	ELEMENT
		\endcode
		*/
		FlowResults fetch(size_t d, const char* rname, const csmp::Model<3>& m)
		{
			auto rref = m.Region(rname);
			const size_t elements = rref.Elements();
			const size_t md = containsVolumeElements(rref) ? 3 : 2;
			const MatrixElement<3> mbp(md==2);			
			vector<double> evols(elements);
			vector<vector<double>> vel_comps(md, vector<double>(elements)), pg_comps(md, vector<double>(elements));

			const Index v_key(m.Database().StorageKey(((string) "velocity " + to_string(d)).c_str()));
			const Index pg_key(m.Database().StorageKey(((string) "pressure gradient " + to_string(d)).c_str()));
			const Index am_key(m.Database().StorageKey("mechanical aperture"));

			size_t eid(0);
			VectorVariable<3> vvar;
			FlowResults fr(md, elements);
			for (auto eit = rref.ElementsBegin(); eit != rref.ElementsEnd(); ++eit, ++eid) {
				if (mbp(*eit))
					evols[eid] = (*eit)->Volume();
				else
					evols[eid] = (*eit)->Volume()*(*eit)->Read(am_key);
				(*eit)->Read(v_key, vvar);
				if (isnan(evols[eid])) {
					(*eit)->Out();
					cin.get();
				}
				for (size_t id(0); id < md; ++id)
					vel_comps[id][eid] = vvar(id);
				(*eit)->Read(pg_key, vvar);
				for (size_t id(0); id < md; ++id)
					pg_comps[id][eid] = vvar(id);
			}

			fr.assign_volumes(evols.begin(), evols.end());
			for (size_t id(0); id < md; ++id) {
				fr.assign_components(FlowResults::Data::velocity, id, vel_comps[id].begin(), vel_comps[id].end());
				fr.assign_components(FlowResults::Data::pressure_gradient, id, pg_comps[id].begin(), pg_comps[id].end());
			}
			return fr;
		}


	} // !tperm
} // !csmp