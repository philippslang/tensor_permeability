#ifndef TP_RESULTS_H
#define TP_RESULTS_H

#include <vector>
#include <numeric>

namespace csmp {
	namespace tperm {


		/// Results container for single pressure experiment
		class FlowResults
		{
		public:
			enum class Data { velocity, pressure_gradient };

			FlowResults() = delete;
			/// Dimension and element count ctor
			explicit FlowResults(size_t, size_t);

			template <typename InputIterator>
			void assign_volumes(InputIterator first, InputIterator last) {
				vols_.assign(first, last);
			}

			template <typename InputIterator>
			void assign_components(Data r, size_t component, InputIterator first, InputIterator last) {
				if (r == Data::velocity)
					vel_comps_.at(component).assign(first, last);
				else
					pgrad_comps_.at(component).assign(first, last);
			}

			size_t dim() const { return pgrad_comps_.size(); }

			const std::vector<double>& volumes() const { return vols_; }

			const std::vector<double>& components(Data r, size_t component) const {
				if (r == Data::velocity)
					return vel_comps_.at(component);
				return pgrad_comps_.at(component);
			}

			virtual double domain_volume() const { return accumulate(vols_.begin(), vols_.end(), 0.); }

		private:
			std::vector<double> vols_;                       ///< Element volumes
			std::vector<std::vector<double>> pgrad_comps_;   ///< Pressure gradient components
			std::vector<std::vector<double>> vel_comps_;     ///< Velocity components		
		};


		/// Creates sampling region using a boundary distance criterion
		class UpscaledTensor
		{
		public:
			UpscaledTensor() = delete;
			/// 3D/2D
			explicit UpscaledTensor(size_t d) : d_(d), t_(d*d, 0.) {}

			/// Row-column access
			double& operator()(size_t r, size_t c) { return t_.at(row_column_to_idx(r, c)); }

			/// Row-column const access
			double  operator()(size_t r, size_t c) const { return t_.at(row_column_to_idx(r, c)); }

			const std::vector<double>& raw() const { return t_; }

			size_t dim() const { return d_; }

		private:
			size_t row_column_to_idx(size_t r, size_t c) const { return r*d_ + c; }

			size_t d_;
			std::vector<double> t_;
		};


	} // !tperm
} // !csmp

#endif // !TP_RESULTS_H