#include "Grid2D.hpp"
#include "SimpleSolver.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

SimpleSolver::SimpleSolver(const Grid2D& grid, const config& cfg): grid_(grid), config_(cfg){
    mu_ = config_.RHO*config_.U_LID * grid.lx() / config_.RE;

    u_.resize(grid_.u_nx(), grid_.u_ny(), 0.0);
    v_.resize(grid_.v_nx(), grid_.v_ny(), 0.0);
    p_.resize(grid_.p_nx(), grid_.p_ny(), 0.0);
    p_prime_.resize(grid_.p_nx(), grid_.p_ny(), 0.0);
    d_u_.resize(grid_.u_nx(), grid_.u_ny(), 0.0);
    d_v_.resize(grid_.v_nx(), grid_.v_ny(), 0.0);
    u_sys_.resize(grid_.u_nx(), grid_.u_ny());
    v_sys_.resize(grid_.v_nx(), grid_.v_ny());
    p_sys_.resize(grid_.p_nx(), grid_.p_ny());
    apply_boundary_conditions();
}

void SimpleSolver::apply_boundary_conditions(){
    for(int j=0;j<grid_.u_ny();j++){
        u_(0,j) = 0.0;  // Left wall
        u_(grid_.nx(),j) = 0.0; //rigth wall
    }

        for (int i = 0; i < grid_.v_nx(); ++i) {
        v_(i, 0) = 0.0;             // Bottom wall
        v_(i, grid_.ny()) = 0.0;    // Top lid
    }
}

// void SimpleSolver::assemble_and_solve_u(double& u_res){
//     const double dx = grid_.dx();
//     const double dy = grid_.dy();
//     const double rho = config_.RHO;
//     const double D_e = mu_*dy/dx;
//     const double D_w = mu_*dy/dx;
//     const double D_n = mu_*dx/dy;
//     const double D_s = mu_*dx/dy;

// }