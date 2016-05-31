#include "model_io.h"
#include "ANSYS_Model3D.h"
#include "settings.h"
#include "PropertyDatabase.h"

using namespace std;

namespace csmp {
	namespace tperm {

		 
		bool write_vfile(const char* vfname, const csmp::PropertyDatabase<3>& pdb)
		{
			ofstream vfile(vfname);
			if (!vfile.is_open())
				return false;
			vfile << pdb;
			vfile.close();
			return true;
		}


		/**
		Appends csmp customary `-regions.txt` to `fnamepref`.
		*/
		bool write_rfile(const char* fnamepref, const vector<string>& rnames)
		{
			auto fname = (string)fnamepref + "-regions.txt";
			ofstream rfile(fname);
			if (!rfile.is_open())
				return false;
			rfile << "regions file\nno properties\n";
			for (const auto& rn : rnames)
				rfile << rn << endl;
			rfile.close();
			return true;
		}


		/// Removes line element regions for 3D models
		void cleanup(csmp::Model<3>& m)
		{
			if (containsVolumeElements(m.Region("Model")))
				for (auto it = m.UniqueRegionsBegin(); it != m.UniqueRegionsEnd(); ++it)
					if (containsLineElements(it->second) && it->first != "Model")
					{
						m.RemoveRegion(it->first.c_str(), true);
						it = m.UniqueRegionsBegin();
					}
		}

		
		/**
		## Option I (ANSYS)

		Expects `JSON` data in form (for ANSYS generated binary files)

			"file name": "csp" 
			"format": "icem" 

		If a region file `rfile-regions.txt` is to be used, the setting

			"regions file": "rfile" 

		has to be present. If not, all Icem families in the `.asc` file will be loaded as csmp::Region.
		As an additional option, all regions to be included can be provided as a setting, in which case
		a temporary regions file (`tmp-regions.txt`) will be created to load the model with:

			"regions": ["MATRIX", "FRACTURES", "BOUNDARY1",...]
		
		## Option II (CSMP)

		For (for CSMP binary model)
		
			"file name": "csp" 
			"format": "csmp binary"

		Removes line element regions if 3D model. Returns nullptr if options not valid.
		*/
		unique_ptr<csmp::Model<3>> load_model(const Settings& s)
			{
				Settings ls(s.json); // local copy that is mutable
				unique_ptr<csmp::Model<3>> pMod(nullptr);
				const bool two_d = false;
				const auto mfname = ls.json["file name"].get<string>();
				unique_ptr<csmp::PropertyDatabase<3>> pdb = property_database(two_d);
				const char* vfname = "variables.txt";
				if (!write_vfile(vfname, *pdb))
					return pMod; // is null at this point
				const auto option = ls.json["format"].get<string>();
				if (ls.json.count("regions")) {
					string temp_rfname = "tmp";
					ls.json["regions file"] = temp_rfname;
					write_rfile(temp_rfname.c_str(), ls.json["regions"].get<vector<string>>());
				}
				if (option == "icem") // icem (ansys) bin file based
					if (ls.json.count("regions file"))
						pMod.reset(new ANSYS_Model3D(mfname.c_str(), ls.json["regions file"].get<string>().c_str(), vfname, true, true, true));
					else
						pMod.reset(new ANSYS_Model3D(mfname.c_str(), vfname, true, true, false, true));
				else if (option == "csmp binary") //csmp bin file based 
					pMod.reset(new Model<3>(mfname.c_str()));
				if (pMod)
					cleanup(*pMod);
				return pMod;
			}


		/**
		These are the minimum required variables to solve the pressure problem dim times
		and post-process permeability.
		*/
		unique_ptr<csmp::PropertyDatabase<3>> property_database(bool two_d)
		{
			unique_ptr<csmp::PropertyDatabase<3>> pPdb(new PropertyDatabase<3>());
			pPdb->Verbose(false);
			// for the pressure problem
			pPdb->AddProperty("fluid volume source", "m3 s-1", SCALAR, ELEMENT, -1.0, 1.0);
			pPdb->AddProperty("fluid pressure", "Pa", SCALAR, NODE, -1.0E-5, 1.0E+9);
			pPdb->AddProperty("conductivity", "m2 Pa-1 s-1", TENSOR, ELEMENT, 1.0E-25, 1.0); // is m3/Pa.s for fracs
			// matrix only
			pPdb->AddProperty("permeability", "m2", TENSOR, ELEMENT, 1.0E-25, 1.0E-8); 
			// fractures only
			pPdb->AddProperty("hydraulic aperture", "m", TENSOR, ELEMENT, 0., 1.0);
			pPdb->AddProperty("mechanical aperture", "m", SCALAR, ELEMENT, 0., 1.0);
			// results
			const size_t dim = two_d ? 2 : 3;
			for (size_t i(0); i < dim; ++i) {
				const string vn = "velocity " + to_string(i);
				pPdb->AddProperty(vn.c_str(), "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				const string pn = "pressure gradient " + to_string(i);
				pPdb->AddProperty(pn.c_str(), "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
			}
			return pPdb;
		}


	} // !tperm
} // !csmp