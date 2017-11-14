#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w)
{
    int row_size = w.size() + 1;
    int col_size = W + 1;
    vector<vector<int>> knapsack_vals;
    knapsack_vals.resize(row_size, vector<int>(col_size));
    for (int i = 0; i < row_size; i ++)
        knapsack_vals[i][0] = 0;
    for (int i = 0; i < col_size; i ++)
        knapsack_vals[0][i] = 0;

    for (int row = 1; row < row_size; row ++)
    {
        for (int col = 1; col < col_size; col ++)
        {
            knapsack_vals[row][col] = knapsack_vals[row - 1][col];
            if (w[row - 1] <= col)
            {
                int val = knapsack_vals[row - 1][col - w[row - 1]] + w[row - 1];
                if (val > knapsack_vals[row][col])
                {
                    knapsack_vals[row][col] = val;
                }
            }
        }
    }

    //std::cout << "\n\nFinal Matrix\n";
    //for (int row = 0; row < row_size; row ++)
    //{
    //    for (int col = 0; col < col_size; col ++)
    //    {
    //        std::cout << knapsack_vals[row][col] << " ";
    //    }
    //    std::cout << "\n";
    //}

    return knapsack_vals[row_size - 1][col_size - 1];
}

void test_knapsack(void)
{
    int n, W;
    while (1)
    {
        W = rand() % 9999;
        n = rand() % 300;
        vector<int> w(n);
        for (int i = 0; i < n; i++) {
            w[i] = rand() % 99999;
        }
        std::cout << "\nW = " << W << " n = " << n << "\nweights: ";
        for (int i = 0; i < n; i++) {
            std::cout << w[i] << " ";
        }
        std::cout << optimal_weight(W, w) << "test complete\n";
    }
}

int main() {
    //test_knapsack();
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
