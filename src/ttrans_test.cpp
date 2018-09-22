#include "catch.hpp"
#include "ttrans.h"

using namespace csmp::tperm;
using namespace csmp;
using namespace std;

TEST_CASE("tensor and vector transformations unit test")
{
    array<csmp::Point<3>, 3> pts;
    pts.fill(csmp::Point<3>(0., 0., 0.));
    for (size_t i(0); i < 3; ++i)
        pts[i][i] = 1.0;
    array<csmp::VectorVariable<3>, 3> eloc;
    local_uvecs(pts, eloc);
    for (size_t i(0); i < 3; ++i)
        REQUIRE(eloc[i].Length() == Approx(1.0).epsilon(0.001));
}
