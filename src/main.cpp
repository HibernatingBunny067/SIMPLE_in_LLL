#include "Field2D.hpp"
#include "Grid2D.hpp"
#include "LinearSolver.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>


int main(){

    const int ny = 50*2;
    const int nx = 50*2;
    Grid2D grid(nx,ny,1.0,1.0);
    const double dx = grid.dx();
    const double dy = grid.dy();
    const double pi = std::acos(-1.0);


    Field2D phi(nx,ny,1.0);
    Field2D phi_exact(nx,ny,0.0);

    //analytical solution
    for(int j=0;j<ny;j++){
        for(int i=0;i<nx;i++){
            phi_exact(i,j) = std::sin(pi*grid.xp(i)) * std::sin(pi*grid.yp(j));
        }
    }


    Stencil2D sys(nx,ny);
    const double D_x = dy / dx;
    const double D_y = dx /dy;


    for(int j=0;j<ny;j++){
        for(int i=0;i<nx;i++){
            double aE = (i==nx-1)?0.0:D_x;
            double aW = (i==0)?0.0:D_x;
            double aN = (j==ny-1)?0.0:D_y;
            double aS = (j==0)?0.0:D_y;


            double aP = aW + aE + aS + aN;
            if (i == 0)      aP += 2.0 * D_x;
            if (i == nx - 1) aP += 2.0 * D_x;
            if (j == 0)      aP += 2.0 * D_y;
            if (j == ny - 1) aP += 2.0 * D_y;

            sys.aE(i, j) = aE;
            sys.aW(i, j) = aW;
            sys.aN(i, j) = aN;
            sys.aS(i, j) = aS;
            sys.aP(i, j) = aP;

            // Integrated volumetric source term
            double S = -2.0 * pi * pi * std::sin(pi * grid.xp(i)) * std::sin(pi * grid.yp(j));
            sys.b(i, j) = -S * dx * dy;

        }
    }


    
    double omega = 1.6;
    std::cout << "Testing SOR solver on " << nx << "x" << ny << " gird with " << omega << " relaxation parameter..\n";
    auto result = LinearSolver::solve_sor(phi,sys,0,nx-1,0,ny-1,omega,5000,1e-10);

    std::cout << "Converged in: " << result.iterations << " iterations\n";
    std::cout << "Initial Residual: " << std::scientific <<result.initial_residual << "\n";
    std::cout <<"Final Residual: " << std::scientific << result.final_residual << "\n";

        double max_err = 0.0;
    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            max_err = std::max(max_err, std::abs(phi(i, j) - phi_exact(i, j)));
        }
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Max Error vs Analytical: " << max_err << "\n";
    std::cout << "Expected O(dx^2) error:  ~" << (dx * dx) << "\n\n";
    if (max_err < 0.002) {
        std::cout << ">>> TEST PASSED: Your Linear Solver is validated and mathematically exact! <<<\n";
    }
    return 0;

}