#ifndef TP_OMEGAGENERATOR_H
#define TP_OMEGAGENERATOR_H

#include <vector>
#include <memory>


namespace csmp {
	// forwards
	struct Index;
	template<size_t> class Model;
	template<size_t> class Element;


	namespace tperm {
		class Omega;

		/// ABC for omega generators
		class OmegaGenerator
		{
		public:
			using OmegaPtrColl = std::vector<std::shared_ptr<Omega>>;

			OmegaGenerator() {};
			virtual ~OmegaGenerator() {};

			virtual OmegaPtrColl generate(const csmp::Model<3>&) const = 0;			
		};

		/** \class OmegaGenerator

		Abstract base class for omega generators. Errors should be detected during ctors, and not during the generate call.
		*/

		/// Fills provided Omega, deletes whatever in it
		void omega_from_elements(const std::vector<Element<3>*>&, const csmp::Index&, Omega&);


	} // !tperm
} // !csmp

#endif // !TP_OMEGAGENERATOR_H