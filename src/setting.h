#ifndef TP_SETTING_H
#define TP_SETTING_H

#include "json.hpp"

namespace csmp {
	namespace tperm {

		/// Container for solver/configurator control settings.
		/**
		The class currently encapsulate nlohmann::json. It is the interface to user-provided settings, 
		which, for now, are JSON based and somewhat tightly coupled.
		*/
		class Setting
		{
		public:
			Setting();
			
			void initialize(const nlohmann::json& j);

			bool empty() const;

			template<typename T>
			T value() const {
				return j_.begin().value();
			}

		private:
			nlohmann::json j_;			
		};

	} // !tperm
} // !csmp

#endif // !TP_SETTING_H