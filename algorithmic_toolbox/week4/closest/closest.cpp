#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;


double minimal_distance(vector<int> x, vector<int> y) {
    //write your code here
    if (x.size() == 2)
        return sqrt(pow((x[1] - x[0]), 2) + pow((y[1] - y[0]), 2));
    return 0.;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
