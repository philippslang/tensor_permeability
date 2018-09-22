#include "sort_boundaries.h"
#include "model_io.h"

#include "Model.h"

using namespace std;

namespace csmp {
namespace tperm {

/**
In this form we just check whether `LEFT` is present, then we're
dealing with the legacy format (works for both 2 and 3D)
The returned vector so far returns boundaries for the 3D case, the
2D case can discard the last entry

@todo This needs a more rigorous implementation, and perhaps a check
if all boundaries exist, even though this should trigger later exceptions at
a lower level
@todo Region support
*/
vector<pair<string, string>> opposing_boundary_names(const Model<3> &m) {
  if (m.ContainsBoundary((string) "LEFT"))
    return {{"LEFT", "RIGHT"}, {"TOP", "BOTTOM"}, {"FRONT", "BACK"}};
  return {{"BOUNDARY1", "BOUNDARY2"},
          {"BOUNDARY3", "BOUNDARY4"},
          {"BOUNDARY5", "BOUNDARY6"}};
}

/**
Generates tperm::Boundary objects and sorts them into
tperm::OpposingBoundaries.

@todo Different boundaries (internal) from settings file
@todo Region support
*/
Boundaries sort_boundaries(const Model<3> &m, const Settings &s) {
  const size_t d = dimensionality(m);
  auto obnames = opposing_boundary_names(m);
  Boundaries bds(d);
  for (size_t i(0); i < d; ++i) {
    bds[i].first.assign(m.Boundary(obnames.at(i).first).NodesBegin(),
                        m.Boundary(obnames.at(i).first).NodesEnd()); // in
    bds[i].second.assign(m.Boundary(obnames.at(i).second).NodesBegin(),
                         m.Boundary(obnames.at(i).second).NodesEnd()); // out
  }
  return bds;
}

} // !tperm
} // !csmp