/** @file */
#ifndef SBOUNDARIES_H
#define SBOUNDARIES_H

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "boundaries.h"

namespace csmp {
template <size_t> class Model;

namespace tperm {
class Settings;

/// Returns sorted Boundaries of the Model
Boundaries sort_boundaries(const csmp::Model<3> &, const Settings &);

/// Returns list of opposing boundary names depending on naming convention, i.e.
/// `TOP...` or `BOUNDARY1`...
std::vector<std::pair<std::string, std::string>>
opposing_boundary_names(const csmp::Model<3> &);

} // !tperm
} // !csmp

#endif // !SBOUNDARIES_H