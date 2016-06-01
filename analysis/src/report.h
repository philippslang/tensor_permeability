/** @file */
#ifndef TP_REPORT_H
#define TP_REPORT_H

#include <map>
#include <string>

namespace csmp {
	template<size_t> class Model;

	namespace tperm {
		class UpscaledTensor;

		/// Computes upscaled permeability tensor 
		void report(const std::map<std::string, UpscaledTensor>&, const Model<3>&, std::string fname = "");

		void vtu(const std::map<std::string, UpscaledTensor>&, const Model<3>&, const char* fname = "results");


	} // !tperm
} // !csmp

#endif // !TP_REPORT_H