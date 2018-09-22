/** @file */
#ifndef ELOPS_H
#define ELOPS_H

#include "Element.h"

#include <array>

namespace csmp {
namespace tperm {

    inline void nd_coords(const Element<3>* const eptr, std::array<csmp::Point<3>, 3>& pts)
    {
        for (size_t i(0); i < 3; ++i)
            pts[i] = eptr->N(i)->Coordinate();
    }

} // !tperm
} // !csmp

#endif // !ELOPS_H