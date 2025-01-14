#include <vector>
#include <iostream>
#include <exception>
#include "DirectedEdge.cpp"

class EdgeWeightedDigraph
{
private:
    int V;                          // number of vertices in this digraph
    int E;                          // number of edges in this digraph
    std::vector<DirectedEdge> *adj; // adj[v] = adjacency list for vertex v
    int *indegree;                  // indegree[v] = indegree of vertex v

public:
    EdgeWeightedDigraph(int V) : V(V), E(0), indegree(new int[V]), adj(new std::vector<DirectedEdge>[V])
    {
    }
    EdgeWeightedDigraph(std::istream &in)
    {
        in >> V;
        indegree = new int[V];
        adj = new std::vector<DirectedEdge>[V];

        in >> E;
        for (int i = 0; i < E; i++)
        {
            int v, w;
            in >> v >> w;
            validateVertex(v);
            validateVertex(w);
            double weight;
            in >> weight;
            addEdge(DirectedEdge(v, w, weight));
        }
    }
    // TODO: rule of three

    int Vertices()
    {
        return V;
    }

    int Edges()
    {
        return E;
    }

    void validateVertex(int v)
    {
        if (v < 0 || v >= V)
        {
            throw std::invalid_argument("vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(V - 1));
        }
    }

    void addEdge(DirectedEdge e)
    {
        int v = e.from();
        int w = e.to();
        validateVertex(v);
        validateVertex(w);
        adj[v].push_back(e);
        indegree[w]++;
        E++;
    }

    std::vector<DirectedEdge> getAdj(int v)
    {
        validateVertex(v);
        return adj[v];
    }

    int outdegree(int v)
    {
        validateVertex(v);
        return adj[v].size();
    }

    int indegree(int v)
    {
        validateVertex(v);
        return indegree[v];
    }

    std::vector<DirectedEdge> edges()
    {
        std::vector<DirectedEdge> list;
        for (int v = 0; v < V; v++)
        {
            for (DirectedEdge e : getAdj(v))
            {
                list.push_back(e);
            }
        }
        return list;
    }
};