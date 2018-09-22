/** @file */
#ifndef TTRANS_H
#define TTRANS_H

#include "Point.h"
#include "TensorVariable.h"

#include <array>

// These methods are inlined and work with mutable parameters instead of returns
// for performance
namespace csmp {
namespace tperm {

/// Generates local unit vector system w.r.t. global coordinate system
/**
The plane represented by the three points `pts` is assumed the
fracture plane. The third local `e3loc`
is normal to this plane, the other two `eloc` are on the plane.
Assumes global coordinate system as
`e1(1,0,0)`, `e2(0,1,0)`, and `e3(0,0,1)`. Local e2loc (y-axis) is
in global y-x plane, such that
`e2loc` is the projection of `e2` onto plane created by three
points.
*/
inline void local_uvecs(const std::array<csmp::Point<3>, 3> &pts,
                        std::array<csmp::VectorVariable<3>, 3> &eloc) {
  // element/fracture unit normal and local coordinate vectors
  eloc[2] = pts[1] - pts[0];
  eloc[2] = eloc[2].CrossProduct(pts[2] - pts[0]);
  eloc[2].EuclideanNormalize(); // e3loc is unit normal to element(fracture)
                                // plane, and local z coord
  eloc[1](0) = 0.;
  eloc[1](1) = 1.;
  eloc[1](2) = 0.; // global e2
  eloc[1] = eloc[1] - eloc[1].ProjectOnto(eloc[2]);
  eloc[1].EuclideanNormalize(); // xloc is global y projection on plane
  eloc[0] = eloc[1].CrossProduct(eloc[2].P());
}

/// Transformation tensor for rotation operations
inline void trans_tensor(const std::array<csmp::VectorVariable<3>, 3> &eloc,
                         VectorVariable<3> &dcosine,
                         TensorVariable<3> &ttrans) {
  for (size_t i(0); i < 3; ++i) {
    dcosine = eloc[i].DirectionCosine();
    for (size_t j = 0; j < 3; ++j)
      ttrans(i, j) = dcosine(j);
  }
}

/// Tensor rotation from tvar to tvart using ttrans
inline void rot_tensor(const TensorVariable<3> &ttrans,
                       const TensorVariable<3> &tvar,
                       TensorVariable<3> &tvart) {
  tvart = ttrans.Transposed() * tvar;
  tvart *= ttrans;
}

} // !tperm
} // !csmp

#endif // !TTRANS_H