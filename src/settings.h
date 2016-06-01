#ifndef TP_SETTING_H
#define TP_SETTING_H

#include "json.hpp"

#include <exception>
#include <string>

namespace csmp {
	namespace tperm {


		/// Exception for wrong json access request
		class json_null : public std::exception
		{
			const char* miss_obj_name_;
		public:
			explicit json_null(const char* missing_object) : miss_obj_name_(missing_object) {}
			virtual const char* what() const throw() { return std::string("JSON object " + (std::string)miss_obj_name_ + " doesn't exist").c_str(); }
		};


		/// JSON Container for application settings
		class Settings
		{
		public:
			Settings() noexcept;
			/// Throws if not available
			Settings(const Settings&, const char* sub_object);

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