#include <iostream>
#include <cassert>

int gcd_naive(int a, int b) {
    int current_gcd = 1;
    for (int d = 2; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            if (d > current_gcd) {
                current_gcd = d;
            }
        }
    }
    return current_gcd;
}

int gcd_fast(int a, int b)
{
    int new_b = b;
    while (new_b != 0)
    {
        new_b = a % b;
        a = b;
        b = new_b;
    }
    return a;
}

int test_gdcs()
{
    while (1)
    {
        int a = rand() % 10000000 + 1;
        int b = rand() % 10000000 + 1;
        int fast_gcd = gcd_fast(a, b);
        int naive_gcd = gcd_naive(a, b);
        std::cout << "A = " << a << " B = " << b << "\t\t";
        std::cout << "Fast: " << fast_gcd << "\tNaive: " << naive_gcd << "\n";
        assert(fast_gcd == naive_gcd);
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << gcd_fast(a, b) << std::endl;
    //test_gdcs();
    return 0;
}
