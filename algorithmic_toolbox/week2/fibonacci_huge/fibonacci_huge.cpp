#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_fibonacci_huge_fast(long long n, long long m)
{
    if (n < 1)
        return 0;
    if (m < 2)
        return 0;

    long long pd_len = 3;
    long long prev_mod = 1;
    long long current_mod = 1;
    while (prev_mod != 0 || current_mod != 1)
    {
        prev_mod = current_mod;
        current_mod = get_fibonacci_huge_naive(pd_len, m);
        pd_len ++;
        //std::cout << current_mod << " ";
    }
    pd_len -= 2;
    //std::cout << "\nPeriod length = " << pd_len << "\n";
    return get_fibonacci_huge_naive(n % pd_len, m);
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
    //for (int i = 1; i < 7; i ++)
    //{
    //    std::cout << "\nFi % " << i << "\t";
    //    for (int j = 0; j < 80; j ++)
    //    {
    //        std::cout << get_fibonacci_huge_naive(j, i) << " ";
    //    }
    //}
}
