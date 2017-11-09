#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
    vector<int> summands(n, 0);
    //write your code here
    int i = 0;
    while (n > 0)
    {
        i ++;
        if (n >= (2 * i + 1))
        {
            summands[i - 1] = i;
        }
        else
        {
            summands[i - 1] = n;
        }
        n -= summands[i - 1];
    }
    summands.erase(std::remove(summands.begin(), summands.end(), 0),
            summands.end());
    summands.shrink_to_fit();
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
