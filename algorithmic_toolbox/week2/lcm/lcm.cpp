#include <iostream>
#include <cassert>

long long lcm_naive(long long a, long long b) {
    for (long l = 1; l <= (long long) a * b; ++l)
        if (l % a == 0 && l % b == 0)
            return l;

    return (long long) a * b;
}

long long lcm_fast(long long a, long long b)
{
    if (a < 1 || b < 1)
    {
        return 0;
    }
    long long original_a = a;
    long long original_b = b;
    long long current_gcd = 1;
    long long new_b = b;
    while (new_b != 0)
    {
        new_b = a % b;
        a = b;
        b = new_b;
    }
    long long lcm = (long long)original_a * (long long)original_b /
        (long long)a;
    return lcm;
}

void test_lcm(void)
{
    std::cout << "Start test\n";
    while (1)
    {
        long long a = rand() % 100000 + 1;
        long long b = rand() % 100000 + 1;
        std::cout << "A = " << a << " B = " << b << "\t\t";
        long long fast_lcm = lcm_fast(a, b);
        long long naive_lcm = lcm_naive(a, b);
        std::cout << "Fast: " << fast_lcm << "\tNaive: " << naive_lcm << "\n";
        assert(fast_lcm == naive_lcm);
    }
}

int main() {
    long long a, b;
    //test_lcm();
    std::cin >> a >> b;
    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}
