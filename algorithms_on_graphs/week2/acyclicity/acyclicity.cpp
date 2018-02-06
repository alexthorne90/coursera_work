#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<bool> &visited, vector<vector<int>> adj,
        int *res, int start)
{
    visited[v] = true;
    //std::cout << "Visited " << v << "    ";
    for (int i = 0; i < adj[v].size(); i ++)
    {
        //std::cout << "checking " << adj[v][i] << "   ";
        if (!visited[adj[v][i]])
        {
            //std::cout << " need to explore\n";
            explore(adj[v][i], visited, adj, res, start);
        }
        else if (adj[v][i] == start)
        {
            //std::cout << " found cycle\n";
            *res = 1;
        }
    }
    //std::cout << "Finished exploration\n";
}

int acyclic(vector<vector<int> > &adj) {
    //write your code here
    for (int i = 0; i < adj.size(); i ++)
    {
        vector<bool> visited_this_exploration(adj.size(), false);
        int res = 0;
        //std::cout << "\nNew Exploration\n\n";
        explore(i, visited_this_exploration, adj, &res, i);
        if (res == 1)
        {
            return 1;
        }
    }
    return 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    //std::cout << "\n\n";
    //for (int i = 0; i < adj.size(); i ++)
    //{
    //    std::cout << i << " -> ";
    //    for (int j = 0; j < adj[i].size(); j ++)
    //    {
    //        std::cout << adj[i][j] << " ";
    //    }
    //    std::cout << "\n";
    //}
    //std::cout << "\n\n";
    std::cout << acyclic(adj);
}
