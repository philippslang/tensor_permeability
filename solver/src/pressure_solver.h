/** @file */
#ifndef TPSOLVER_H
#define TPSOLVER_H


namespace csmp {
	class Index;
	template<size_t> class Model;

	namespace tperm {
		class Boundary;
		class Boundaries;

		/// Computes conductivity subsequently used in the solver
		void conductivity(csmp::Model<3>&);

		/// Solves pressure problem for all boundary pairs and stores in model
		void solve(const Boundaries&, csmp::Model<3>&);

		/// Dirichlet `fluid pressure` boundary condition
		void dirichlet_scalar_bc(const tperm::Boundary&, const Index&, double);

		/// Solves steady-state diffusion
		void solve_pressure(csmp::Model<3>&);


	} // !tperm
} // !csmp

#endif // !SOLVER_H