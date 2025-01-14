#include <list>
#include <vector>
#include <queue>
#include <iostream>

void BFS(const std::vector<std::list<int>> &g, int start)
{
    std::cout << "----BFS----\n";
    std::vector<int> visited(g.size(), false);
    visited[start] = true;
    std::deque<int> q;
    q.push_back(start);
    while (!q.empty())
    {
        int node = q.front();
        q.pop_front();
        std::cout << node << ' ';

        for (int neighbour : g[node])
        {
            if (!visited[neighbour])
            {
                q.push_back(neighbour);
                visited[neighbour] = true;
            }
        }
    }

    std::cout << "\n----END BFS----\n";
}

void DFS(const std::vector<std::list<int>> &g, int start)
{
    std::cout << "----DFS----\n";
    std::vector<bool> visited(g.size(), false);
    visited[start] = true;
    std::deque<int> q;
    q.push_front(start);
    while (!q.empty())
    {
        int node = q.front();
        q.pop_front();
        std::cout << node << ' ';

        for (int neighbour : g[node])
        {
            if (!visited[neighbour])
            {
                q.push_front(neighbour);
                visited[neighbour] = true;
            }
        }
    }

    std::cout << "\n----END DFS----\n";
}

void DfsRec(const std::vector<std::list<int>> &g, int x, std::vector<bool> &visited)
{
    visited[x] = true;
    std::cout << x << ' ';
    for (int neighbour : g[x])
    {
        if (!visited[neighbour])
        {
            DfsRec(g, neighbour, visited);
        }
    }
}

void DfsRec(const std::vector<std::list<int>> &g)
{
    std::cout << "----DFS RECURSIVE----\n";
    std::vector<bool> visited(g.size(), false);
    for (int i = 0; i < g.size(); i++)
    {
        if (!visited[i])
        {
            DfsRec(g, i, visited);
        }
    }

    std::cout << "\n----END DFS RECURSIVE----\n";
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::list<int>> undirectedgraph(n);
    for (size_t i = 0; i < m; i++)
    {
        int from, to;
        std::cin >> from >> to;
        undirectedgraph[from].push_back(to);
        undirectedgraph[to].push_back(from);
    }
    BFS(undirectedgraph, 0);
    DFS(undirectedgraph, 0);
    DfsRec(undirectedgraph);
}