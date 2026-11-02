#pragma once

#include "Grid2D.hpp"
#include "Field2D.hpp"
#include "LinearSolver.hpp"
#include <string>


class SimpleSolver{

    public:
        struct config{
            double RE = 100.0;
            double U_LID = 1.0;
            double RHO = 1.0;
            double ALPHA_u = 0.7;
            double ALPHA_v = 0.7;
            double ALPHA_p = 0.3;
            int max_iters = 5000;
            double convergence_tol = 1e-5;
            int linear_max_iters_norm = 20;
            int linear_max_iters_p = 100;
            double linear_tol_mom = 1e-4;
            double linear_tol_p = 1e-5;
            double sor_omega_p = 1.6;
            int print_interval = 50;
        };

        SimpleSolver(const Grid2D& grid, const config& config);

        bool solve();

        const Field2D& u() const { return u_;}
        const Field2D& v() const { return v_;}
        const Field2D& p() const { return p_;}

        const Grid2D& grid() const { return grid_; }
        const config& confid() const { return config_; }

        void get_cell_centered_velocity(Field2D& u_center, Field2D& v_center) const;

        void export_centerlines_csv(const std::string& filename) const;


        private:
            Grid2D grid_;
            config config_;
            double mu_;

            Field2D u_;
            Field2D v_;
            Field2D p_;
            Field2D p_prime_;

            Field2D d_u_;
            Field2D d_v_;

            Stencil2D u_sys_;
            Stencil2D v_sys_;
            Stencil2D p_sys_;

            void assemble_and_solve_u(double& u_res);
            void assemble_and_solve_v(double& v_res);
            double assemble_and_solve_p_prime();
            void correct_fields();
            void apply_boundary_conditions();
};