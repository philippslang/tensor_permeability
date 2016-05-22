#include "model_io.h"
#include "ANSYS_Model3D.h"
#include "settings.h"
#include "PropertyDatabase.h"

using namespace std;

namespace csmp {
	namespace tperm {


		void write_vfile(const char* vfname)
		{
			ofstream vfile(vfname);
			auto pdb = property_database();
			vfile << *pdb;
			vfile.close();
		}
		
		
		unique_ptr<csmp::Model<3>> load_model(const Settings& s)
			{
				unique_ptr<csmp::Model<3>> pMod(nullptr);
				const char* mfname = s.json["file name"].get<string>().c_str();
				const char* vfname = "variables.txt";
				write_vfile(vfname);
				bool rfile = false;
				pMod.reset(new ANSYS_Model3D(mfname, vfname, true, true, rfile, true));
				return pMod;
			}


		unique_ptr<csmp::PropertyDatabase<3>> property_database(bool two_d)
		{
			unique_ptr<csmp::PropertyDatabase<3>> pPdb(new PropertyDatabase<3>());
			pPdb->AddProperty("fluid volume source", "m3 s-1", SCALAR, ELEMENT, -1.0, 1.0);
			pPdb->AddProperty("fluid pressure", "Pa", SCALAR, NODE, -1.0E-5, 1.0E+9);
			pPdb->AddProperty("permeability", "m2", TENSOR, ELEMENT, 1.0E-25, 1.0E-8); // is m3 for fracs
			pPdb->AddProperty("conductivity", "m2 Pa-1 s-1", TENSOR, ELEMENT, 1.0E-25, 1.0);// is m3/Pa.s for fracs
			pPdb->AddProperty("fracture permeability", "m2", TENSOR, ELEMENT, 1.0E-25, 1.0E-8); // is m2 for fracs
			pPdb->AddProperty("fracture conductivity", "m2 Pa-1 s-1", TENSOR, ELEMENT, 1.0E-25, 1.0);// is m2/Pa.s for fracs
			if (two_d) {
				pPdb->AddProperty("velocity I", "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				pPdb->AddProperty("pressure gradient I", "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
				pPdb->AddProperty("velocity II", "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				pPdb->AddProperty("pressure gradient II", "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
			}
			else {
				pPdb->AddProperty("velocity I", "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				pPdb->AddProperty("pressure gradient I", "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
				pPdb->AddProperty("velocity II", "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				pPdb->AddProperty("pressure gradient II", "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
				pPdb->AddProperty("velocity III", "m s-1", VECTOR, ELEMENT, -1.0E+2, 1.0E+2);
				pPdb->AddProperty("pressure gradient III", "Pa m-1", VECTOR, ELEMENT, -1.0E+20, 1.0E+20);
			}			
			return pPdb;
		}


	} // !tperm
} // !csmp