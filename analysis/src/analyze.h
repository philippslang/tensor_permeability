/** @file */
#ifndef TP_ANALYZE_H
#define TP_ANALYZE_H

#include <vector>

namespace csmp {
	namespace tperm {
		class FlowResults;
		class UpscaledTensor;

		/// Computes upscaled permeability tensor 
		UpscaledTensor analyze(const std::vector<FlowResults>&);


	} // !tperm
} // !csmp

#endif // !TP_ANALYZE_H