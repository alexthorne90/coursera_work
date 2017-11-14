#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

vector<int> retrace_steps_from_full_sequence(int n, vector<int> full_sequence)
{
    std::vector<int> path;
    int current_num = n;
    path.push_back(current_num);
    while (current_num != 1)
    {
        int minus_one_attempt = current_num - 1;
        int div_two_attempt = current_num / 2;
        int div_three_attempt = current_num / 3;
        int current_min = minus_one_attempt;
        if (current_num % 2 == 0)
        {
            if (full_sequence[div_two_attempt] < full_sequence[current_min])
                current_min = div_two_attempt;
        }
        if (current_num % 3 == 0)
        {
            if (full_sequence[div_three_attempt] < full_sequence[current_min])
                current_min = div_three_attempt;
        }
        path.push_back(current_min);
        current_num = current_min;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> sequence_dynamic(int n)
{
    std::vector<int> full_sequence(n + 1, n + 1);
    full_sequence[0] = 0;
    full_sequence[1] = 0;
    for (int i = 2; i <= n; i ++)
    {
        int minus_one_attempt = i - 1;
        int div_two_attempt = i / 2;
        int div_three_attempt = i / 3;
        int current_min = minus_one_attempt;
        if (i % 2 == 0)
        {
            if (full_sequence[div_two_attempt] < full_sequence[current_min])
                current_min = div_two_attempt;
        }
        if (i % 3 == 0)
        {
            if (full_sequence[div_three_attempt] < full_sequence[current_min])
                current_min = div_three_attempt;
        }
        full_sequence[i] = full_sequence[current_min] + 1;
    }
    return retrace_steps_from_full_sequence(n, full_sequence);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = sequence_dynamic(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
