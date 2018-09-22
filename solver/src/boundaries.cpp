#include "boundaries.h"

namespace csmp {
namespace tperm {

    Boundary::Boundary()
        : nodes_()
    {
    }

    /// Initializes three empty Boundary pairs
    Boundaries::Boundaries()
        : boundaries_(3)
    {
    }

    /// Initializes d empty Boundary pairs
    Boundaries::Boundaries(size_t d)
        : boundaries_(d)
    {
    }

} // !tperm
} // !csmp