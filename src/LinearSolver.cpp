#include "LinearSolver.hpp"
#include <cmath>
#include <algorithm>


double LinearSolver::compute_residual(
    const Field2D& phi,
    const Stencil2D& sys,
    int i_start,
    int i_end,
    int j_start,
    int j_end
){

    double max_res = 0.0;

    for(int j=j_start;j<=j_end;j++){
        for(int i=i_start;i<=i_end;i++){

            double rhs = sys.b(i,j);
            if(i+1 < sys.nx) rhs += sys.aE(i,j)*phi(i+1,j);
            if(i-1 >= 0)     rhs += sys.aW(i,j)*phi(i-1,j);
            if(j+1 < sys.ny) rhs += sys.aN(i,j)*phi(i,j+1);
            if(j-1 >= 0)     rhs += sys.aS(i,j)*phi(i,j-1);

            double res = std::abs(rhs - sys.aP(i,j)*phi(i,j));
            max_res = std::max(max_res,res);

        }
    }

    return max_res;

}

LinearSolver::SolverResult LinearSolver::solve_sor(
    Field2D& phi,
    const Stencil2D& sys,
    int i_start,
    int i_end,
    int j_start,
    int j_end,
    double omega,
    int max_iterations,
    double tol
){

    SolverResult result;
    result.initial_residual = compute_residual(phi,sys,i_start,i_end,j_start,j_end);
    result.final_residual = result.initial_residual;
    result.iterations  = 0;
    result.converged = (result.initial_residual <= tol);

    if(result.converged) return result;


    for(int iter=1;iter<=max_iterations;iter++){
        for(int j=j_start;j<=j_end;j++){
            for(int i=i_start;i<=i_end;i++){
                double rhs = sys.b(i,j);
                if(i+1 < sys.nx) rhs += sys.aE(i,j)*phi(i+1,j);
                if(i-1 >= 0)     rhs += sys.aW(i,j)*phi(i-1,j);
                if(j+1 < sys.ny) rhs += sys.aN(i,j)*phi(i,j+1);
                if(j-1 >= 0)     rhs += sys.aS(i,j)*phi(i,j-1);

                double phi_gs = rhs/sys.aP(i,j);
                phi(i,j) = (1.0-omega)*phi(i,j) + omega*phi_gs;
            }
        }
        result.iterations = iter;


        if(iter%5 == 0 || iter == max_iterations){
            double res = compute_residual(phi,sys,i_start,i_end,j_start,j_end);
            result.final_residual = res;

            if(res <= tol){
                result.converged = true;
                break;
            }
        }
    }

    return result;
}