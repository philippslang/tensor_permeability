#ifndef TP_RESULTS_H
#define TP_RESULTS_H

#include <vector>


namespace tperm {


	/// Creates sampling region using a boundary distance criterion
	class FlowResults 
	{
	public:
		/// 3D default
		FlowResults();
		/// 3D/2D
		explicit FlowResults(size_t);

	private: 
		std::vector<std::vector<double>> pgrad_comps_;   ///< Pressure gradient components
		std::vector<std::vector<double>> vel_comps_;     ///< Velocity components
		std::vector<double> vols_;                       ///< Element volumes
	};


	/// Creates sampling region using a boundary distance criterion
	class UpscaledTensor
	{
	public:
		/// 3D default
		UpscaledTensor();
		/// 3D/2D
		explicit UpscaledTensor(size_t);

		/// Row-column access
		double& operator()(size_t r, size_t c) { return t_.at(row_column_to_idx(r, c)); }
		/// Row-column const access
		double  operator()(size_t r, size_t c) const { return t_.at(row_column_to_idx(r, c)); }

	private:
		size_t row_column_to_idx(size_t r, size_t c) const { return r*d_ + c; }

		size_t d_;
		std::vector<double> t_;
	};


} // !tperm

#endif // !TP_RESULTS_H