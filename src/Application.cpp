#include <iostream>

#include "Standard.h"
#include "Vector.h"

int main()
{
    ShowStart();
    gmath::Vector3 a(2, 6, 4);
    gmath::Vector3 b(3, 5, -3);
    gmath::Vector3 c(1, 1, 1);
    std::cout << "The first is " << a << std::endl;
    std::cout << "The second is " << b << std::endl;
    // Log("Enter Vec3");
    // std::cin >> c;
    std::cout << "The input is " << c << std::endl;
    c = a;
    std::cout << "The assignment is " << c << std::endl;
    std::cout << "The sum is " << (a + b) << std::endl;
    std::cout << "The diff is " << (a - b) << std::endl;
    std::cout << "The comparision A==B is " << (a == b) << std::endl;
    std::cout << "The comparision A!=B is " << (a != b) << std::endl;
    std::cout << "The mag of " << a << " is " << a.GetMagnitude() << std::endl;
    float mag = a.GetMagnitude();
    std::cout << "The sqr mag of " << a << " is " << a.GetSqrMagnitude() << std::endl;
    a.Normalize();
    std::cout << "The normalized of " << a << " is " << a << std::endl;
    a = a * mag;
    std::cout << "The positive of " << a << " is " << +a << std::endl;
    std::cout << "The negative of " << a << " is " << -a << std::endl;
    std::cout << "The thrice of " << a << " is " << a * 3 << std::endl;
    std::cout << "The twice of " << a << " is " << 2 * a << std::endl;
    std::cout << "The half of " << a << " is " << a / 2 << std::endl;
    std::cout << "The displacemnet b/w " << a << " to " << b << " is " << gmath::GetDisplacement(a, b) << std::endl;
    std::cout << "The distance b/w " << a << " to " << b << " is " << gmath::GetDistance(a, b) << std::endl;
    std::cout << "The sqr displacemnet b/w " << a << " to " << b << " is " << gmath::GetSqrDistance(a, b) << std::endl;
    std::cout << "The midpoint b/w " << a << " to " << b << " is " << gmath::Lerp(a, b, 0.5) << std::endl;
    std::cout << "The max b/w " << a << " to " << b << " is " << gmath::GetMax(a, b) << std::endl;
    std::cout << "The min b/w " << a << " to " << b << " is " << gmath::GetMin(a, b) << std::endl;
    std::cout << "The Normalized val of " << a << " is " << gmath::GetNormalized(a) << std::endl;
    std::cout << "The dot product b/w " << a << " and " << b << " is " << gmath::DotProduct(a, b) << std::endl;
    std::cout << "The dot vector b/w " << a << " and " << b << " is " << gmath::DotVector(a, b) << std::endl;
    std::cout << "The cross product b/w " << a << " and " << b << " is " << gmath::Cross(a, b) << std::endl;
    ShowEnd();
    return 0;
}