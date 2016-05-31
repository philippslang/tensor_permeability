/** @file */
#ifndef TPSOLVER_H
#define TPSOLVER_H


namespace csmp {
	struct Index;
	template<size_t> class Model;

	namespace tperm {
		class Boundary;
		class Boundaries;


		/// Solves pressure problem for all boundary pairs and stores in model
		void solve(const Boundaries&, csmp::Model<3>&);

		/// Dirichlet `fluid pressure` boundary condition
		void dirichlet_scalar_bc(const tperm::Boundary&, const Index&, double);

		/// Solves steady-state diffusion
		void solve_pressure(csmp::Model<3>&);

		/// Computes and stores pressure gradient and velocity
		void pgrad_and_vel(csmp::Model<3>&, size_t);


	} // !tperm
} // !csmp

#endif // !SOLVER_H