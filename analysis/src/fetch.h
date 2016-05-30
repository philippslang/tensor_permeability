/** @file */
#ifndef FETCH_H
#define FETCH_H

#include <vector>
#include <map>

#include "results.h"

namespace csmp {
	template<size_t> class Model;

	namespace tperm {		

		/// Returns upscaled tensors for all  regions in model that contain `rtag`
		std::map<std::string, UpscaledTensor> fetch(const csmp::Model<3>&, const char* rtag = "omega");

		/// Returns FlowResults of the given region, as many as model dimensions
		FlowResults fetch(size_t, const char*, const csmp::Model<3>&);

		
	} // !tperm
} // !csmp

#endif // !FETCH_H