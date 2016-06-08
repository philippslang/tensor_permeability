/** @file */
#ifndef TP_MAKEOMEGAS_H
#define TP_MAKEOMEGAS_H

#include <map>
#include <memory>


namespace csmp {
	template<size_t> class Model;

	namespace tperm {		
		class Settings;
		class OmegaGenerator;

		/// Returns sampling regions generator
		std::unique_ptr<OmegaGenerator> make_omega_generator(const Settings&);

		
	} // !tperm
} // !csmp

#endif // !TP_MAKEOMEGAS_H