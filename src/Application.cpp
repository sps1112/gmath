#include <iostream>

#include "Standard.h"
#include "Vector.h"

int main()
{
    gmath::Vector3 a(2, 2, 3);
    gmath::Vector3 b(1, 2, 3);
    a = a + b;
    //gmath::Vector3 b(4, -3, 6);
    // gmath::Vector3 c = gmath::up3;
    std::cout << a << std::endl;
    // std::cout << (a + 3 * b - c / 0.25) << std::endl;
    return 0;
}