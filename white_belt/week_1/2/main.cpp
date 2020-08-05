#include <iostream>
#include <string>

int main() {
    std::string first, second, third;
    std::cin >> first >> second >> third;
    if (first >= second)
    {
        first = second;
    }
    if (first >= third)
    {
        first = third;
    }
    std::cout << first;
    return 0;
}
