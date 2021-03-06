#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<bool> &visited, vector<vector<int>> adj)
{
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i ++)
    {
        if (!visited[adj[v][i]])
        {
            explore(adj[v][i], visited, adj);
        }
    }
}

int DFS(vector<bool> &visited, vector<vector<int>> adj)
{
    int cc = 0;
    for (int i = 0; i < adj.size(); i ++)
    {
        if (!visited[i])
        {
            explore(i, visited, adj);
            cc ++;
        }
    }
    return cc;
}

int number_of_components(vector<vector<int> > &adj) {
    int res = 0;
    //write your code here
    vector<bool> visited(adj.size(), false);
    res = DFS(visited, adj);
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    std::cout << number_of_components(adj);
}
