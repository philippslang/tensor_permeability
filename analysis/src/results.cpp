#include "results.h"

using namespace std;

namespace csmp {
namespace tperm {

FlowResults::FlowResults(size_t d, size_t elmts)
    : vols_(elmts), pgrad_comps_(d, vector<double>(elmts)),
      vel_comps_(d, vector<double>(elmts)) {}

} // ! tperm
} // !csmp