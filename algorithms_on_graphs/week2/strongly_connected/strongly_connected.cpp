#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<int> &used, vector<vector<int>> adj,
        vector<int> &order, int *order_count)
{
    used[v] = 1;
    //std::cout << "Visited " << v << "    ";
    for (int i = 0; i < adj[v].size(); i ++)
    {
        //std::cout << "checking " << adj[v][i] << "   ";
        if (!used[adj[v][i]])
        {
            //std::cout << " need to explore\n";
            explore(adj[v][i], used, adj, order, order_count);
        }
    }
    order[*order_count] = v;
    *order_count = *order_count + 1;
    //std::cout << "Finished exploration\n";
}

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x)
{
    //write your code here
    int order_count = 0;
    for (int i = 0; i < adj.size(); i ++)
    {
        if (!used[i])
        {
            //std::cout << "New Exploration   ";
            explore(i, used, adj, order, &order_count);
        }
    }
}

void scc_explore(int v, vector<int> &used, vector<vector<int>> adj)
{
    used[v] = 1;
    //std::cout << "Visited " << v << "    ";
    for (int i = 0; i < adj[v].size(); i ++)
    {
        //std::cout << "checking " << adj[v][i] << "   ";
        if (!used[adj[v][i]])
        {
            //std::cout << " need to explore\n";
            scc_explore(adj[v][i], used, adj);
        }
    }
    //std::cout << "Finished exploration\n";
}

int number_of_strongly_connected_components(vector<vector<int>> adj,
        vector<vector<int>> adj_reverse)
{
    int result = 0;
    //write your code here
    vector<int> used(adj.size(), 0);
    vector<int> scc_used(adj.size(), 0);
    vector<int> order(adj.size(), 0);
    dfs(adj_reverse, used, order, 0);
    for (int i = order.size() - 1; i >= 0; i--)
    {
        //std::cout << order[i] + 1 << " ";
        if (!scc_used[order[i]])
        {
            //std::cout << "Scc explore " << order[i] << "\n";
            scc_explore(order[i], scc_used, adj);
            result ++;
        }
    }
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > adj_reverse(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj_reverse[y - 1].push_back(x - 1);
    }
    std::cout << number_of_strongly_connected_components(adj, adj_reverse);
}
