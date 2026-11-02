#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>


class Grid2D{
    
    //Staggered grid used for the computation 

    private:
        int nx_, ny_;
        double lx_, ly_;
        double dx_, dy_;

    public:

        Grid2D(int nx, int ny, double lx=1.0, double ly=1.0){
            nx_ = nx;
            ny_ = ny;
            lx_ = lx;
            ly_ = ly;
            dx_ = lx_ / nx_;
            dy_ = ly_ / ny_;
        }

        int nx() const { return nx_; }
        int ny() const { return ny_; }
        double lx() const { return lx_; }
        double ly() const { return ly_; }
        double dx() const { return dx_; }
        double dy() const { return dy_; }

        //Stagerred faces for the vector fields
        int u_nx() const { return nx_+1; }
        int u_ny() const { return ny_; }
        int v_nx() const { return nx_; }
        int v_ny() const { return ny_+1; }

        //Cell centers for the scalar fields
        int p_nx() const { return nx_; }
        int p_ny() const { return ny_; }

        double xp(int i) const { return (i+0.5)*dx_; }
        double yp(int j) const { return (j+0.5)*dy_; }

        double xu(int i) const { return i*dx_; }
        double yu(int j) const { return (j+0.5)*dy_; }

        double xv(int i) const { return (i+0.5)*dx_; }
        double yv(int j) const { return j*dy_; }
};