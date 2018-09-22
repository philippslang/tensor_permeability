#ifndef TP_OMEGACORNERCONFIG_H
#define TP_OMEGACORNERCONFIG_H

#include "configurator.h"

#include "Point.h"

#include <array>
#include <vector>

namespace csmp {

namespace tperm {

/// Creates sampling region using a boundary distance criterion
class OmegaCornerPointsConfigurator : public Configurator {
public:
  OmegaCornerPointsConfigurator() = delete;
  /// As many regions as corner point pairs (box), regions named `omega_0...n-1`
  explicit OmegaCornerPointsConfigurator(
      const std::vector<std::array<csmp::Point<3>, 2>> &);

  virtual bool configure(Model &) const override;

private:
  /// Returns points with all minimum components and all maximum components of
  /// the provided points
  std::array<csmp::Point<3>, 2>
  min_max(const std::array<csmp::Point<3>, 2> &cpts) const {
    csmp::Point<3> min, max;
    for (size_t i(0); i < 3; ++i) {
      min[i] = cpts[0][i] < cpts[1][i] ? cpts[0][i] : cpts[1][i];
      max[i] = cpts[0][i] > cpts[1][i] ? cpts[0][i] : cpts[1][i];
    }
    return {min, max};
  }

  // False if strictly greated or strictly less than bounds
  bool within_bounds(const csmp::Point<3> &pt,
                     const std::array<csmp::Point<3>, 2> &minmax) const {
    for (size_t xyz(0); xyz < 3; ++xyz)
      if (pt[xyz] < minmax[0][xyz] || pt[xyz] > minmax[1][xyz])
        return false; // not within min-max bounds
    return true;
  }

  const std::vector<std::array<csmp::Point<3>, 2>> cpts_;
};

/** \class OmegaCornerPointsConfigurator

Creates non-unique csmp::Region `omega0..x` that contains all
csmp::Element within boxes of provided corner
point pairs.

@deprecated We don't use omega configurators - look for the
equivalent generator
*/

} // !tperm
} // !csmp

#endif // !TP_OMEGACORNERCONFIG_H