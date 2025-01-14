#include "DirectedEdge.h"

DirectedEdge::DirectedEdge(int v, int w, double weight) : v(v), w(w), mWeight(weight)
{
}

int DirectedEdge::from()
{
    return v;
}

int DirectedEdge::to()
{
    return w;
}

double DirectedEdge::weight()
{
    return mWeight;
}