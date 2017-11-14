#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
    //write your code here
    int row_size = str1.size() + 1;
    int col_size = str2.size() + 1;
    vector<vector<int>> distance_matrix;
    distance_matrix.resize(row_size, vector<int>(col_size));
    for (int i = 0; i < row_size; i ++)
        distance_matrix[i][0] = i;
    for (int i = 0; i < col_size; i ++)
        distance_matrix[0][i] = i;

    for (int row = 1; row < row_size; row ++)
    {
        for (int col = 1; col < col_size; col ++)
        {
            int insertion = distance_matrix[row][col - 1] + 1;
            int deletion = distance_matrix[row - 1][col] + 1;
            int match = distance_matrix[row - 1][col - 1];
            int mismatch = distance_matrix[row - 1][col - 1] + 1;
            if (str1[row - 1] == str2[col - 1])
            {
                distance_matrix[row][col] =
                    std::min({insertion, deletion, match});
            }
            else
            {
                distance_matrix[row][col] =
                    std::min({insertion, deletion, mismatch});
            }
        }
    }
    std::cout << "\n\nFinal Matrix\n";
    for (int row = 0; row < row_size; row ++)
    {
        for (int col = 0; col < col_size; col ++)
        {
            std::cout << distance_matrix[row][col] << " ";
        }
        std::cout << "\n";
    }
    return distance_matrix[row_size - 1][col_size - 1];;
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
