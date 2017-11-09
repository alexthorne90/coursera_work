#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool my_comparator(string a, string b)
{
    std::string ab_str = a + b;
    std::string ba_str = b + a;
    int ab = std::stoi(ab_str, 0, 0);
    int ba = std::stoi(ba_str, 0, 0);
    //std::cout << "\na + b = " << ab;
    //std::cout << "\nb + a = " << ba;
    //if (ab < ba)
    //    std::cout << "\t Select " << ba;
    //else
    //    std::cout << "\t Select " << ab;
    //std::cout <<"\n";
    if (ab <= ba)
        return false;
    else
        return true;
}

string largest_number(vector<string> a) {
    //write your code here
    std::stringstream ret;
    std::sort(a.begin(), a.end(), my_comparator);
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
