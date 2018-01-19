#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using std::string;
using std::vector;
typedef unsigned long long ull;
const ull p = pow(2, 63) - 25;
const ull x = rand() % p;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

ull PolyHash(string s)
{
    ull hash = 0;;
    for (int i = (s.length() - 1); i >= 0; i --)
    {
        hash = (hash * x + s[i]) % p;
    }
    return hash;
}

vector<ull> PrecomputeHashes(string full_text, int pattern_length)
{
    vector<ull> h(full_text.length() - pattern_length + 1);
    string s = full_text.substr((full_text.length() - pattern_length),
            pattern_length);
    h[full_text.length() - pattern_length] = PolyHash(s);
    ull y = 1;
    for (int i = 1; i <= pattern_length; i ++)
    {
        y = (y * x) % p;
    }
    for (int i = (full_text.length() - pattern_length - 1); i >= 0; i --)
    {
        h[i] = (x * h[i+1] + full_text[i] - y * full_text[i + pattern_length])
            % p;
    }
    return h;
}

vector<ull> RabinKarpPrecomputed(string full_text, string pattern)
{
    vector<ull> result;
    ull pattern_hash = PolyHash(pattern);
    vector<ull> precomputed_hashes =
        PrecomputeHashes(full_text, pattern.length());
    for (ull i = 0; i <= (full_text.length() + pattern.length()); i ++)
    {
        if (pattern_hash != precomputed_hashes[i])
        {
            continue;
        }
        else if (pattern.compare(full_text.substr(i, pattern.length())) == 0)
        {
            result.push_back(i);
        }
    }
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    Data input = read_input();
    vector<ull> results = RabinKarpPrecomputed(input.text, input.pattern);
    for (ull i = 0; i < results.size(); i ++)
        std::cout << results[i] << " ";
    return 0;
}
