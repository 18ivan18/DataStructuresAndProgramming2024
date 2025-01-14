#include <list>
#include <vector>
#include <queue>
#include <iostream>

#define INF 0x3f3f3f3f

/*
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/
int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::list<std::pair<int, int>>> weightedgraph(n);
    for (size_t i = 0; i < m; i++)
    {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        weightedgraph[from].push_back({to, weight});
        weightedgraph[to].push_back({from, weight});
    }

    int src = 0;

    // Create a priority queue to store vertices that
    // are being preprocessed. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>
        pq;

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    std::vector<int> dist(n, INF);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push({0, src});
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
    distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        // 'i' is used to get all adjacent vertices of a
        // vertex
        for (auto &&i : weightedgraph[u])
        {
            // Get vertex label and weight of current
            // adjacent of u.
            int v = i.first;
            int weight = i.second;

            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}