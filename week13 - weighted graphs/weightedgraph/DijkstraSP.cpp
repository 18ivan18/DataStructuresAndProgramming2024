#include <queue>
#include <vector>
#include "DirectedEdge.cpp"
#include "EdgeWeightedDigraph.cpp"
#include <cmath>

class DijkstraSP
{
private:
    double *distTo;                   // distTo[v] = distance  of shortest s->v path
    std::vector<DirectedEdge> edgeTo; // edgeTo[v] = last edge on shortest s->v path
    std::priority_queue<double> pq;   // priority queue of vertices

    DijkstraSP(EdgeWeightedDigraph G, int s)
    {
        for (DirectedEdge e : G.edges())
        {
            if (e.weight() < 0)
                throw new std::invalid_argument("edge " + e.toString() + " has negative weight");
        }

        distTo = new double[G.Vertices()];
        edgeTo.resize(G.Vertices());

        validateVertex(s);

        for (int v = 0; v < G.Vertices(); v++)
        {
            distTo[v] = INFINITY;
        }
        distTo[s] = 0.0;

        // relax vertices in order of distance from s
        pq.push(s, distTo[s]);
        while (!pq.isEmpty())
        {
            int v = pq.delMin();
            for (DirectedEdge e : G.adj(v))
                relax(e);
        }

        // check optimality conditions
        assert check(G, s);
    }

    // relax edge e and update pq if changed
private
    void relax(DirectedEdge e)
    {
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.weight())
        {
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;
            if (pq.contains(w))
                pq.decreaseKey(w, distTo[w]);
            else
                pq.insert(w, distTo[w]);
        }
    }

    /**
     * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
     * @param  v the destination vertex
     * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
     *         {@code Double.POSITIVE_INFINITY} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
public
    double distTo(int v)
    {
        validateVertex(v);
        return distTo[v];
    }

    /**
     * Returns true if there is a path from the source vertex {@code s} to vertex {@code v}.
     *
     * @param  v the destination vertex
     * @return {@code true} if there is a path from the source vertex
     *         {@code s} to vertex {@code v}; {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
public
    boolean hasPathTo(int v)
    {
        validateVertex(v);
        return distTo[v] < Double.POSITIVE_INFINITY;
    }

    /**
     * Returns a shortest path from the source vertex {@code s} to vertex {@code v}.
     *
     * @param  v the destination vertex
     * @return a shortest path from the source vertex {@code s} to vertex {@code v}
     *         as an iterable of edges, and {@code null} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
public
    Iterable<DirectedEdge> pathTo(int v)
    {
        validateVertex(v);
        if (!hasPathTo(v))
            return null;
        Stack<DirectedEdge> path = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()])
        {
            path.push(e);
        }
        return path;
    }
}