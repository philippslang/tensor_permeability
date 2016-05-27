#ifndef TP_SETTING_H
#define TP_SETTING_H

#include "json.hpp"

namespace csmp {
	namespace tperm {


		/// JSON Container for application settings
		class Settings
		{
		public:
			Settings();
			explicit Settings(nlohmann::json);

			nlohmann::json json;
		};


		/** \class Settings

		The class currently subclasses nlohmann::json. It is the interface to user-provided settings,
		which, for now, are JSON based and somewhat tightly coupled.

		@todo Querying json for non existant entry should force a throw
		*/


	} // !tperm
} // !csmp

#endif // !TP_SETTING_H