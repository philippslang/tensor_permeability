/** @file */
#ifndef TP_ANALYZE_H
#define TP_ANALYZE_H


namespace tperm {
	class FlowResults;
	class UpscaledTensor;

	/// Computes upscaled permeability tensor 
	UpscaledTensor analyze(const FlowResults&);

		
} // !tperm

#endif // !TP_ANALYZE_H