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


		void run_from_file(const char* fn)
		{
			// load settings file
			ifstream f(fn);
			if (!f.is_open())
				throw runtime_error(string("Can't open settings file " + string(fn)));
			Settings s;
			s.json << f;
			f.close();
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
			// report results
			report(omega_tensors, *model);
			// output model
			if (acs.json.count("save final binary"))
				if (acs.json["save final binary"].get<string>() != "")
					save_model(*model, acs.json["save final binary"].get<string>().c_str());
		}


	} // !tperm
} // ! csmp