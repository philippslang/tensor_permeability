/** @file */

#ifndef TP_MODELIO_H
#define TP_MODELIO_H

#include <memory>
#include <vector>
#include <array>
#include <string>
#include <algorithm>


namespace csmp {
	template<size_t> class Model;
	template<size_t> class PropertyDatabase;

	namespace tperm {
		// forwards
		class Settings;

		/// Writes application specific variables file
		bool write_vfile(const char* fname, const csmp::PropertyDatabase<3>&);

		/// Writes region file
		bool write_rfile(const char* fnamepref, const std::vector<std::string>& rnames);

		/// Loads csmp::Model based on tperm::Settings
		std::unique_ptr<csmp::Model<3>> load_model(const Settings&);

		/// Generates app specific property database
		std::unique_ptr<csmp::PropertyDatabase<3>> property_database(bool two_d = false);

		/// Saves csmp::Model to native bindary
		bool save_model(const csmp::Model<3>&, const char*);

		/// Determines if DFN only
		bool has_matrix(const csmp::Model<3>&);

		/// Determines if fractures present
		bool has_fractures(const csmp::Model<3>&);

		/// Based on presence of 'FRONT' or 'BOUNDARY5'
		bool is_two_D(const csmp::Model<3>&);

		/// Wrapper for two_D
		size_t dimensionality(const csmp::Model<3>&);

		/// Based on presence of 'FRONT' or 'BOUNDARY5' and volume elements
		bool is_dfn(const csmp::Model<3>&);

		/// Identification of outer model boundary based on naming convention
		inline bool is_main_boundary_id(std::string blname)
		{
			static const std::array<std::string, 12> outer = { "TOP", "BOTTOM", "LEFT", "RIGHT", "FRONT", "BACK" ,
				"BOUNDARY1", "BOUNDARY2", "BOUNDARY3", "BOUNDARY4", "BOUNDARY5", "BOUNDARY6" };
			auto it = find(outer.begin(), outer.end(), blname);
			if (it != outer.end())
				return true;
			return false;
		}

	} // !tperm
} // !csmp

#endif // !TP_MODELIO_H