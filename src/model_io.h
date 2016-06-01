/** @file */

#ifndef TP_MODELIO_H
#define TP_MODELIO_H

#include <memory>
#include <vector>
#include <string>

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
		std::unique_ptr<csmp::PropertyDatabase<3>> property_database(bool two_d);

		/// Saves csmp::Model to native bindary
		bool save_model(const csmp::Model<3>&, const char*);

	} // !tperm
} // !csmp

#endif // !TP_MODELIO_H