#include "report.h"
#include "results.h"

#include "json.hpp"

#include <fstream>

using namespace std;
using json = nlohmann::json;

namespace csmp {
	namespace tperm {


		void report(const std::map<std::string, UpscaledTensor>& omega_tensors, const Model<3>& m)
		{
			json results = json::object();
			json omegas = json::object();
			for (const auto& mit : omega_tensors) {
				json o = json::object();
				o["tensor"] = mit.second.raw();
				omegas[mit.first.c_str()] = o;
			}
			results["sampling regions"] = omegas;
			std::ofstream f("results.json");
			if (f.is_open()) {
				f << results;
				f.close();
			}
		}


	} // !tperm
} // !csmp