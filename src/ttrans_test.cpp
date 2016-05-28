#include "catch.hpp"
#include "ttrans.h"


using namespace csmp::tperm;
using namespace csmp;
using namespace std;


TEST_CASE("tensor and vector transformations unit test") {
	array<csmp::Point<3>, 3> pts;
	pts.fill(csmp::Point<3>(0., 0., 0.));
	for (size_t i(0); i < 3; ++i)
		pts[i][i] = 1.0;
	array<csmp::VectorVariable<3>, 3> eloc;
	local_uvecs(pts, eloc);
	for (size_t i(0); i < 3; ++i)
		REQUIRE(eloc[i].Length() == Approx(1.0).epsilon(0.001));
}


TEST_CASE("tensor rotation") {
	const TensorVariable<3> rot_tens(PLAIN, 0., -1.0, 0., 1.0, 0., 0., 0., 0., 1.);
	TensorVariable<3> var_loc(PLAIN, 1.0, 0.5, 0., 0., 0.5, 0., 0.2, 0., 0.);	
	TensorVariable<3> var_glob_rot_pow, var_glob_pow_rot;
	// transform then do mot
	trans_tensor(rot_tens, var_loc, var_glob_rot_pow);
	var_glob_rot_pow.Power(3.0);
	var_glob_rot_pow /= 12.0;
	// mod then transform
	var_loc.Power(3.0);
	var_loc /= 12.0;
	trans_tensor(rot_tens, var_loc, var_glob_pow_rot);
	// both ops should result in equal tensors
	REQUIRE(var_glob_pow_rot == var_glob_rot_pow);
}

