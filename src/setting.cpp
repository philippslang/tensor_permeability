#include "setting.h"

namespace csmp {
	namespace tperm {

		Setting::Setting() : j_(){

		}

		void Setting::initialize(const nlohmann::json& j) {
			j_ = j;
		}

		bool Setting::empty() const {
			return j_.empty();
		}

	} // !tperm
} // ! csmp