#include "fetch.h"
#include "Model.h"
#include "results.h"
#include "bpreds.h"
#include "analyze.h"
#include "model_io.h"
#include "omega.h"

#include <iterator>
#include <algorithm>

using namespace std;

namespace csmp {
	namespace tperm{


		UpscaledTensor post_process(const UpscaledTensor& raw)
		{
			const size_t d = raw.dim();
			UpscaledTensor r(raw);
			r(0, 1) = r(1, 0) = (r(0, 1) + r(1, 0)) / 2.;
			if (d == 3) {
				r(0, 2) = r(2, 0) = (r(0, 2) + r(2, 0)) / 2.;
				r(1, 2) = r(2, 1) = (r(1, 2) + r(2, 1)) / 2.;
			}
			return r;
		}


		vector<string> omega_names(size_t n)
		{
			vector<string> onames(n, "omega");
			if (n != 1) {
				for (size_t i(0); i < n; ++i)
					onames[i] = (string)"omega_" + to_string(i);
			}
			return onames;
		}


		/**
		@todo Need an indirection here for omega collection, mediator class to loosen coupling with OmegaGenerator
		*/
		map<string, UpscaledTensor> fetch(const csmp::Model<3>& m, const std::map<std::string, std::shared_ptr<Omega>>& ocoll)
		{
			map<string, UpscaledTensor> r;
			const size_t md = dimensionality(m);
			for (const auto& oit : ocoll)
			{				
				vector<FlowResults> fr;
				for (size_t d(0); d < md; ++d)
					fr.push_back(fetch(d, *oit.second, m));
				auto ri_raw = analyze(fr, oit.second->total_volume());
				auto ri = post_process(ri_raw);
				r.insert(std::make_pair(oit.first, ri));
			}
			return r;
		}
		

		/**
		Fetches tperm::FlowResults for experiment `d` and given region.

		Relies on the following variables:

		\code
		// vector variables, for provided dimension d
		pressure gradient 0	pr	Pa m-1	2	-1e+20	1e+20	ELEMENT
		velocity 0	ve	m s-1	2	-100	100	ELEMENT
		\endcode

		@todo We have kind of a redundncy here in that FlowResults contain all element volumes while they're contained in Omega
		*/
		FlowResults fetch(size_t d, const Omega& o, const csmp::Model<3>& m)
		{
			const size_t elements = o.size();
			const size_t md = dimensionality(m);
			const MatrixElement<3> mbp(md==2);		
			const Index v_key(m.Database().StorageKey(((string) "velocity " + to_string(d)).c_str()));
			const Index pg_key(m.Database().StorageKey(((string) "pressure gradient " + to_string(d)).c_str()));

			vector<double> evols(elements);
			vector<vector<double>> vel_comps(md, vector<double>(elements)), pg_comps(md, vector<double>(elements));

			size_t eid(0);
			VectorVariable<3> vvar;
			FlowResults fr(md, elements);
			for (auto eit = o.cbegin(); eit != o.cend(); ++eit, ++eid) {
				evols[eid] = eit->eVol;
				eit->ePtr->Read(v_key, vvar);
				for (size_t id(0); id < md; ++id)
					vel_comps[id][eid] = vvar(id);
				eit->ePtr->Read(pg_key, vvar);
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


		void make_omega_regions(const std::map<std::string, std::shared_ptr<Omega>>& omegas, csmp::Model<3>& m)
		{
			m.UpdateIndices();
			for (const auto& o : omegas) {
				size_t i(0);
				vector<size_t> eids(o.second->size(), 0);
				for_each(o.second->cbegin(), o.second->cend(), [&](const auto& einf) { eids[i++] = einf.ePtr->Idx(); });
				m.FormRegionFrom(o.first.c_str(), eids);
			}
		}


		std::map<std::string, std::shared_ptr<Omega>> named_omegas(const std::vector<std::shared_ptr<Omega>>& omegas)
		{
			std::map<std::string, std::shared_ptr<Omega>> nos;
			const size_t n(omegas.size());
			auto onames = omega_names(n);
			for (size_t i(0); i < n; ++i)
				nos.insert(make_pair(onames[i], omegas[i]));
			return nos;
		}


	} // !tperm
} // !csmp