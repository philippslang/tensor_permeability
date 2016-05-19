#ifndef TP_SETTING_H
#define TP_SETTING_H

#include "json.hpp"

namespace csmp {
	namespace tperm {

		/// Container for solver/configurator control settings.
		class Settings : public nlohmann::json
		{
		};

		/** \class Settings

		The class currently inherits nlohmann::json. It is the interface to user-provided settings,
		which, for now, are JSON based and somewhat tightly coupled.
		*/

	} // !tperm
} // !csmp

#endif // !TP_SETTING_H