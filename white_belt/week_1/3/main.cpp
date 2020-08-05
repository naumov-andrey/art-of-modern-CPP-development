#include <iostream>
#include <cmath>

int main() {
    double a, b, c;
    std::cin >> a >> b >> c;
    if (a != 0.0)
    {
        double d = b * b - 4 * a * c;
        if (d > 0)
        {
            std::cout << (-b + sqrt(d)) / (2 * a) << ' ' << (-b - sqrt(d)) / (2 * a);
        }
        else if (d == 0.0)
        {
            std::cout << -b / (2 * a);
        }
    }
    else if (b != 0.0)
    {
        std::cout << -c / b;
    }
    return 0;
}
