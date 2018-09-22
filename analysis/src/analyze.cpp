#include "analyze.h"
#include "results.h"

#include "DenseMatrix.h"
#include "LUdcmp_Solver.h"

#include <Eigen/Dense>

using namespace std;

namespace csmp {
namespace tperm {

    bool eigen_values(const UpscaledTensor& t, vector<double>& evals, vector<vector<double>>& evecs)
    {
        typedef Eigen::Matrix<double, 3, 3> Matrix3d;
        Matrix3d eigenKeff;
        eigenKeff << t(0, 0), t(0, 1), t(0, 2), t(1, 0), t(1, 1), t(1, 2), t(2, 0), t(2, 1), t(2, 2);
        Eigen::SelfAdjointEigenSolver<Matrix3d> eigensolver(eigenKeff);
        if (eigensolver.info() != Eigen::Success)
            return false;
        //cout << "The eigenvalues of eigenKeff are:\n" << eigensolver.eigenvalues() << endl;
        auto evals_em = eigensolver.eigenvalues();
        auto evecs_em = eigensolver.eigenvectors();
        evals = vector<double>(3, 0.);
        for (size_t i(0); i < 3; ++i)
            evals[i] = evals_em(i, 0);
        evecs = vector<vector<double>>(3, vector<double>(3, 0.));
        for (size_t i(0); i < 3; ++i)
            for (size_t j(0); j < 3; ++j)
                evecs[i][j] = evecs_em(j, i);
        return true;
    }

    /// Pseudo-inverse approach, 3D specialozed
    vector<double> solve_overdet(const DenseMatrix<12>& A, const vector<double>& b)
    {
        DenseMatrix<12> capacity_transposed_product(9, 9);
        DenseMatrix<12> capacity_transposed(9, 12);
        A.Transposed(capacity_transposed);
        A.TransposedProduct(capacity_transposed_product);
        // now becomes rhs first order tensor
        DenseMatrix<12> rhsDenseMatrix(capacity_transposed);
        rhsDenseMatrix *= b;
        vector<double> B(9);
        for (size_t i(0); i < 9; ++i)
            B[i] = rhsDenseMatrix(i, 0);
        // making sparse for solver
        SparseMatrix a(9);
        for (size_t i(0); i < 9; ++i)
            for (size_t ii(0); ii < 9; ++ii)
                a.Assign(i, ii, capacity_transposed_product(i, ii));
        // solve
        vector<double> k(9, 0.);
        LUdcmp_Solver().Solve(a, B, k, 9);
        return k;
    }

    /**
		Assumes unit viscosity.

		@todo Dont like the total_volume bare here
		*/
    UpscaledTensor analyze(const std::vector<FlowResults>& frv, double total_volume)
    {
        const size_t d = frv.size();
        UpscaledTensor r(d);

        // averaging
        const auto& volumes = frv[0].volumes(); // assumption: element info for all exps identical
        const auto elements = volumes.size(); // assumption: element info for all exps identical
        // average xy(z) components for pressure gradients and velocities for each experiment (outer index)
        // and each component (inner index)
        vector<vector<double>> vel_avgs(d, vector<double>(d)), pgrad_avgs(d, vector<double>(d));
        for (size_t I(0); I < d; ++I) // experiment, 0..d-1
            for (size_t c(0); c < d; ++c) { // for each spatial component, 0..d-1
                auto& pgrads = frv[I].components(FlowResults::Data::pressure_gradient, c);
                auto& vels = frv[I].components(FlowResults::Data::velocity, c);
                double pgrad_avg(0.), vel_avg(0.);
                for (size_t eid(0); eid < elements; ++eid) {
                    pgrad_avg += pgrads[eid] * volumes[eid];
                    vel_avg += vels[eid] * volumes[eid];
                }
                vel_avgs[I][c] = vel_avg / total_volume;
                pgrad_avgs[I][c] = pgrad_avg / total_volume;
            }

        // accumulating upscaled darcy problem
        // 1) velocity
        const size_t odiags = d == 3 ? 3 : 1; // number of off-diagonal terms
        vector<double64> u(d * d + odiags, 0.); // rhs, velocity component averages plus zeros
        for (size_t I(0); I < d; ++I)
            for (size_t c(0); c < d; ++c)
                u[I * d + c] = -vel_avgs[I][c];
        // 2) pressure gradients, 3D only from here
        DenseMatrix<12> capacity(12, 9);
        capacity = 0.;
        for (size_t I(0); I < d; ++I)
            for (size_t t(0); t < d; ++t)
                for (size_t c(0); c < d; ++c)
                    capacity(I * 3 + t, t * d + c) = pgrad_avgs[I][c];
        // symmetry conditions
        capacity(9, 1) = capacity(10, 2) = capacity(11, 5) = 1.;
        capacity(9, 3) = capacity(10, 6) = capacity(11, 7) = -1;
        // solving overdetermined system and initializing tensor
        auto k = solve_overdet(capacity, u);
        for (size_t i(0); i < d; ++i)
            for (size_t j(0); j < d; ++j)
                r(i, j) = k[i * d + j];
        return r;
    }

} // !tperm
} // !csmp