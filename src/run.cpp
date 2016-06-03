#include "run.h"
#include "settings.h"
#include "model_io.h"
#include "matrix_configurator_factory.h"
#include "fracture_configurator_factory.h"
#include "configurator.h"
#include "sort_boundaries.h"
#include "pressure_solver.h"
#include "omega_configurator_factory.h"
#include "fetch.h"
#include "report.h"

#include "Model.h"


using namespace std;

namespace csmp {
	namespace tperm {

		/**
		@todo JSON access errors lack specifier
		@todo Minimal input OK check
		@todo Clean up nested checks for optional JSON arguments
		@todo Eigenvalues should be computed independent of json output, stored and used twice, for screen and file
		*/
		void run_from_file(const char* fn)
		{
			// load settings file
			ifstream f(fn);
			if (!f.is_open())
				throw runtime_error(string("Can't open settings file " + string(fn)));
			Settings s;
			s.json << f;
			f.close();
			//cout << setw(4) << s.json;

			// get matrix configurator
			Settings mcs(Settings(s, "configuration"), "matrix");
			MatrixConfiguratorFactory mcf;
			auto mconf = mcf.configurator(mcs);
			// get fracture configurator
			Settings fcs(Settings(s, "configuration"), "fractures");
			FractureConfiguratorFactory fcf;
			auto fconf = fcf.configurator(fcs);
			// get omega generator
			Settings acs(s, "analysis");
			OmegaConfiguratorFactory ocf;
			auto oconf = ocf.configurator(acs);
			// load model...		
			Settings ms(s, "model");
			auto model = load_model(ms);
			// configure material properties
			mconf->configure(*model);
			fconf->configure(*model);
			// sort boundaries
			auto bds = sort_boundaries(*model, s);
			// ready to solve
			solve(bds, *model);
			// generate omegas
			oconf->configure(*model);
			// get upscaled tensors
			auto omega_tensors = fetch(*model);
			// results
			string jres_fname = "";
			if (s.json.count("output")) {
				Settings outs(s, "output");
				if (outs.json.count("save final binary")) // write to csmp binary
					if (outs.json["save final binary"].get<string>() != "")
						save_model(*model, outs.json["save final binary"].get<string>().c_str());
				if (outs.json.count("vtu")) { // write to vtu
					if (outs.json["vtu"].get<bool>())
						vtu(omega_tensors, *model);
					if (outs.json.count("vtu regions"))
						vtu(outs.json["vtu regions"].get<vector<string>>(), *model);
				}
				if (outs.json.count("results file name")) // write to json
					jres_fname = s.json["output"]["results file name"].get<string>();
			}			
			report(omega_tensors, *model, jres_fname.c_str());			
		}


	} // !tperm
} // ! csmp