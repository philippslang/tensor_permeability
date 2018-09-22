#include "run.h"
#include "fetch.h"
#include "fracture_configurator_factory.h"
#include "make_omega_generator.h"
#include "matrix_configurator_factory.h"
#include "model_io.h"
#include "null_configurator.h"
#include "omega.h"
#include "omega_configurator_factory.h"
#include "omega_generator.h"
#include "pressure_solver.h"
#include "report.h"
#include "settings.h"
#include "sort_boundaries.h"

#include "Model.h"

using namespace std;

namespace csmp {
namespace tperm {

    /**
		@todo Minimal input OK check
		*/
    void run(const char* fn)
    {
        // load settings file
        ifstream f(fn);
        if (!f.is_open())
            throw runtime_error(string("Can't open settings file " + string(fn)));
        Settings s;
        s.json << f;
        f.close();
        //cout << setw(4) << s.json;
        run(s);
    }

    /**
		@todo JSON access errors lack specifier
		@todo Check that omegas ar filled/exits
		@todo Clean up nested checks for optional JSON arguments
		@todo Eigenvalues should be computed independent of json output, stored and used twice, for screen and file
		*/
    void run(const Settings& s)
    {
        // empty configurators
        unique_ptr<csmp::tperm::Configurator> mconf = make_unique<csmp::tperm::NullConfigurator>();
        unique_ptr<csmp::tperm::Configurator> fconf = make_unique<csmp::tperm::NullConfigurator>();
        // get matrix configurator
        Settings cs(s, "configuration");
        if (cs.json.count("matrix")) {
            Settings mcs(cs, "matrix");
            mconf = MatrixConfiguratorFactory().configurator(mcs);
        }
        // get fracture configurator
        if (cs.json.count("fractures")) {
            Settings fcs(cs, "fractures");
            fconf = FractureConfiguratorFactory().configurator(fcs);
        }
        // get omega generator
        Settings acs(s, "analysis");
        auto ogen = make_omega_generator(acs);
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
        auto omegas = ogen->generate(*model);
        auto nomegas = named_omegas(omegas);
        // get upscaled tensors
        auto omega_tensors = fetch(*model, nomegas);
        // results
        string jres_fname = "";
        if (s.json.count("output")) {
            Settings outs(s, "output");
            if (outs.json.count("save final binary")) // write to csmp binary
                if (outs.json["save final binary"].get<string>() != "")
                    save_model(*model, outs.json["save final binary"].get<string>().c_str());
            if (outs.json.count("vtu")) { // write to vtu
                if (outs.json["vtu"].get<bool>()) {
                    make_omega_regions(nomegas, *model);
                    vtu(omega_tensors, *model);
                }
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