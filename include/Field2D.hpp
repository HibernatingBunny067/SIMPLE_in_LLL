#pragma once // ensures the header file is included only once during compilation, even if multiple files include it

#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>

class Field2D{
    // A generic 2D matrix buffer class
    // It can be instantiated for any field type - Pressure, Velocities for the initial stage test
    // Instead of using a 2D array, a 1D array of size nx*ny is used which is more efficient due to contiguous memory allocation 
    // Modulo based indexing is used to access the elements of the 2D array

    private:
        // all the data which is never revealed when an object of this class is instantiated
        // something routine in c++ and other OOP language, not directly available in Python 
        int nx_, ny_;
        std::vector<double> data_;

    public:

        Field2D() {
            nx_=0;
            ny_=0;
            data_={};
        }
        Field2D(int nx, int ny, double init_val=0.0){
            nx_ = nx;
            ny_ = ny;
            data_.assign(nx*ny,init_val);
        }
        
        void resize(int nx, int ny, double init_val=0.0){
            nx_ = nx;
            ny_ = ny;
            data_.assign(nx*ny, init_val);
        }

        inline double& operator()(int i, int j){
            // creates an opeartor overloading of the kind p(i,j)
            assert(i >= 0 && i < nx_ && j >=0 && j < ny_ && "Field2D index out of bounds !");
            return data_[j*nx_ + i];
        }

        inline const double& operator()(int i, int j) const{
            assert(i >= 0 && i < nx_ && j >=0 && j < ny_ && "Field2D index out of bounds !");
            return data_[j*nx_ + i];
        }
        
        // std::pair<int,int> size() const{ return {nx_,ny_}; }, might have used this

        int nx() const { return nx_; }
        int ny() const { return ny_; }

        size_t alloc_size() const{ return data_.size(); }

        double* data() { return data_.data(); }

        const double* data() const { return data_.data(); }

        void fill(double val){
            std::fill(data_.begin(),data_.end(),val);
        }

        double norm_inf() const {
            double max_value = 0.0;
            for(double val: data_)
                max_value = std::max(max_value,std::abs(val));
            return max_value;
        }
        
        double norm_l2() const{
            if(data_.empty()) return 0.0;
            double sum_sq = 0.0;
            for(double val: data_)
                sum_sq += val*val;
            
            return std::sqrt(sum_sq/data_.size());
        }
}; //classes end with a semicolon in cpp !
