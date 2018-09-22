/** @file */
#ifndef TPSOLVER_H
#define TPSOLVER_H

#include "boundaries.h"

#include <array>

namespace csmp {
struct Index;
template <size_t>
class Point;
template <size_t>
class Model;
template <size_t>
class TensorVariable;

namespace tperm {

    /// Solves pressure problem for all boundary pairs and stores in model
    void solve(const Boundaries&, csmp::Model<3>&);

    /// Dirichlet `fluid pressure` boundary condition
    void dirichlet_scalar_bc(const tperm::Boundary&, const Index&, double);

    /// Assigns dirichlet to opposing boundaries
    void primary_bc(const Boundaries::OpposingBoundaries&, const Index&, double);

    /// Assigns linearly varying dirichlet to opposing boundaries
    void supplementary_bc(const Boundaries&, const Index&, double, size_t);

    /// Solves steady-state diffusion
    void solve_pressure(csmp::Model<3>&);

    /// Computes and stores pressure gradient and velocity
    void pgrad_and_vel(csmp::Model<3>&, size_t);

} // !tperm
} // !csmp

#endif // !SOLVER_H