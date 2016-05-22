#ifndef TP_MODELIO_H
#define TP_MODELIO_H

#include <memory>

namespace csmp {
	template<size_t> class Model;
	template<size_t> class PropertyDatabase;

	namespace tperm {
		// forwards
		class Settings;

		void write_vfile(const char*);

		std::unique_ptr<csmp::Model<3>> load_model(const Settings&);

		std::unique_ptr<csmp::PropertyDatabase<3>> property_database(bool tensorial_conductivity);

	} // !tperm
} // !csmp

#endif // !TP_MODELIO_H