#pragma once
#include "Field2D.hpp"
// Five point stencil linear solver


struct Stencil2D{
    int nx,ny;
    Field2D aP;
    Field2D aE;
    Field2D aW;
    Field2D aN;
    Field2D aS;
    Field2D b;

    Stencil2D(): nx(0), ny(0) {}

    Stencil2D(int nx_val, int ny_val){
        nx = nx_val;
        ny = ny_val;
        aP.resize(nx, ny, 1.0);
        aW.resize(nx,ny,0.0);
        aE.resize(nx,ny,0.0);
        aN.resize(nx, ny, 0.0);
        aS.resize(nx,ny,0.0);
        b.resize(nx,ny,0.0);
    }

    void resize(int nx_val,int ny_val){
        nx=nx_val;
        ny=ny_val;

        aP.resize(nx, ny,1.0);
        aW.resize(nx,ny,0.0);
        aE.resize(nx,ny,0.0);
        aN.resize(nx, ny, 0.0);
        aS.resize(nx,ny,0.0);
        b.resize(nx,ny,0.0);
    }
};

class LinearSolver{

    public:
        struct SolverResult {
            //Logger for the iterations of the solver
            int iterations;
            double initial_residual;
            double final_residual;
            bool converged;
        };
        /*
        @brief Solves sys*phi = b using Successive Over-Relaxation (SOR)/Gauss-Seidel
        */

        static SolverResult solve_sor(
            Field2D& phi,
            const Stencil2D& sys,
            int i_start,
            int i_end,
            int j_start,
            int j_end,
            double omega = 1.0,
            int max_iters = 1000,
            double tol = 1e-6
        );

        static double compute_residual(
            const Field2D& phi,
            const Stencil2D& sys,
            int i_start, 
            int i_end,
            int j_start,
            int j_end
        );

};