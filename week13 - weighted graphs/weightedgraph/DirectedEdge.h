#ifndef DIRECTED_EDGE
#define DIRECTED_EDGE
class DirectedEdge
{
private:
    const int v;
    const int w;
    const double mWeight;

public:
    DirectedEdge(int v, int w, double weight);
    int from();
    int to();
    double weight();

    std::string toString()
    {
        return std::to_string(v) + "->" + std::to_string(w) + " " + std::to_string(mWeight);
    }
};
#endif