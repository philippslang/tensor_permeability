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

		/// Computes eigen values and eigenvectors
		bool eigen_values(const UpscaledTensor& t, std::vector<double>& evals, std::vector<std::vector<double>>& evecs);


	} // !tperm
} // !csmp

#endif // !TP_ANALYZE_H