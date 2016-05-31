#include "report.h"
#include "results.h"
#include "analyze.h"

#include "json.hpp"

#include <fstream>

using namespace std;
using json = nlohmann::json;

namespace csmp {
	namespace tperm {


		/**
		@todo Implement rounding here
		*/
		void report(const std::map<std::string, UpscaledTensor>& omega_tensors, const Model<3>& m)
		{
			json results = json::object();
			json omegas = json::object();
			vector<double> evals;
			vector<vector<double>> evecs;
			for (const auto& mit : omega_tensors) {
				json o = json::object();
				o["tensor"] = mit.second.raw();				
				eigen_values(mit.second, evals, evecs);
				o["eigen values"] = evals;
				o["eigen vectors"] = evecs;
				omegas[mit.first.c_str()] = o;
			}
			results["sampling regions"] = omegas;
			std::ofstream f("results.json");
			if (f.is_open()) {
				f << std::setw(2) << results;
				f.close();
			}
		}


	} // !tperm
} // !csmp