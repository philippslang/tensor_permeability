/** @file */

#ifndef BPREDS_H
#define BPREDS_H

#include "Element.h"

namespace csmp {
namespace tperm {

    template <size_t dim>
    struct MatrixElement {
        bool twoD_;
        MatrixElement()
            : twoD_(false)
        {
        }
        explicit MatrixElement(bool twoD)
            : twoD_(twoD)
        {
        }
        bool operator()(Element<dim>* const ePtr) const
        {
            if (twoD_)
                return ePtr->IsSurfaceElement(); // 2D
            return ePtr->IsVolumeElement(); // 3D
        }
    };

    template <size_t dim>
    struct FractureElement {
        bool twoD_;
        FractureElement()
            : twoD_(false)
        {
        }
        explicit FractureElement(bool twoD)
            : twoD_(twoD)
        {
        }
        bool operator()(Element<dim>* const ePtr) const
        {
            if (twoD_)
                return ePtr->IsLineElement(); // 2D
            return ePtr->IsSurfaceElement(); // 3D
        }
    };

} // !tperm
} // !csmp

#endif // !BPREDS_H