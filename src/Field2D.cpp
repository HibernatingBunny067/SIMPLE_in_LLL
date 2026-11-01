#include "Field2D.hpp"
#include <iostream>

int main(){
    std:: cout << "\n";
    std:: cout << "Testing Field2D...\n";

    Field2D p(3,3,0.0);

    p(1,1) = -10.5;
    p(2,2) = 5.0;
    p(0,0) = -9;

    std::cout << "p(1, 1) = " << p(1, 1) << " (expected -10.5)\n";
    std::cout << "p(2, 2) = " << p(2, 2) << " (expected 5.0)\n";
    std::cout << "L_inf norm = " << p.norm_inf() << " (expected 10.5)\n";
    std::cout << "L_2 norm   = " << p.norm_l2() << "\n";
    std::cout << "Field2D test complete!\n" << std::endl;

    return 0;
}