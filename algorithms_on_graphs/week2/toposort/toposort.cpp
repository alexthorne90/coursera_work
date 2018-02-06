#include <iostream>
#include <algorithm>
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

vector<int> toposort(vector<vector<int> > adj)
{
    vector<int> used(adj.size(), 0);
    vector<int> order(adj.size(), 0);
    //write your code here
    dfs(adj, used, order, 0);
    //reverse(begin(order), end(order));
    //std::cout << "\n\nFinal Order:";
    //for (int i = 0; i < order.size(); i ++)
    //{
    //    std::cout << order[i] << " ";
    //}
    //std::cout << "\n\n";
    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    vector<int> order = toposort(adj);
    for (int i = order.size() - 1; i >= 0; i--)
    {
        std::cout << order[i] + 1 << " ";
    }
}
