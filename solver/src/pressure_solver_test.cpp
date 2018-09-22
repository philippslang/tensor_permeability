#include "Point.h"
#include "TensorVariable.h"
#include "catch.hpp"

#include <array>

namespace csmp {
namespace tperm {
// pressure_solver.cpp
std::array<double, 4> tpl_plane(const std::array<csmp::Point<3>, 3> &);
}
}

using namespace csmp::tperm;
using namespace csmp;
using namespace std;

TEST_CASE("plane equation unit test") {
  Point<3> a(0.5, 3.0, 4.0), b(1.0, -2.0, 1.0), c(-2.0, 3.0, 2.0);
  array<double, 4> p = tpl_plane({a, b, c});
  REQUIRE(p[0] == Approx(-10.0));
  REQUIRE(p[1] == Approx(-17.0 / 2.0));
  REQUIRE(p[2] == Approx(25.0 / 2.0));
  REQUIRE(p[3] == Approx(-39.0 / 2.0));
}
