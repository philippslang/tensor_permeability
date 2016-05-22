#include "settings.h"

namespace csmp {
	namespace tperm {

		Settings::Settings()
			: json()
		{

		}

		Settings::Settings(nlohmann::json j)
			: json(j)
		{

		}


	} // !tperm
} // ! csmp