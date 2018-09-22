#include "catch.hpp"
#include "omega.h"

#include <algorithm>

using namespace csmp::tperm;
using namespace std;

TEST_CASE("omega unit test")
{
    Omega o;
    REQUIRE(o.size() == 0);
    REQUIRE(o.total_volume() == 0.);
    const size_t s(10);
    const double ev(10.);
    o.resize(s);
    REQUIRE(o.size() == s);
    REQUIRE(o.total_volume() == 0.);
    for_each(begin(o), end(o), [&ev](auto& einf) { einf.eVol = ev; });
    REQUIRE(o.size() == s);
    REQUIRE(o.total_volume() == (double)s * ev);
}
