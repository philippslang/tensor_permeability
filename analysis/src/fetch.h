/** @file */
#ifndef FETCH_H
#define FETCH_H

#include <vector>
#include <map>
#include <memory>

#include "results.h"

namespace csmp {
	template<size_t> class Model;

	namespace tperm {
		class Omega;

		/// Returns upscaled tensors for all omegas
		std::map<std::string, UpscaledTensor> fetch(const csmp::Model<3>&, const std::vector<std::shared_ptr<Omega>>&);

		/// Returns FlowResults of the given region, as many as model dimensions
		FlowResults fetch(size_t, const Omega&, const csmp::Model<3>&);

		/// Assures symmetric tensor by averaging
		UpscaledTensor post_process(const UpscaledTensor&);

		/// Creates a region for each Omega with corresponding name
		void make_omega_regions(const std::vector<std::shared_ptr<Omega>>&, csmp::Model<3>&);

		
	} // !tperm
} // !csmp

#endif // !FETCH_H