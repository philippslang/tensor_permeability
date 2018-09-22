#include "settings.h"

using namespace std;

namespace csmp {
namespace tperm {

    Settings::Settings() noexcept
        : json()
    {
    }

    Settings::Settings(const Settings& s, const char* sub_obj_name)
        : json(s.json[sub_obj_name])
    {
        if (json == nullptr)
            throw json_null(sub_obj_name);
    }

} // !tperm
} // ! csmp