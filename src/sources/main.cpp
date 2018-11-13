#include <iostream>
#include "graphstructure.h"

using namespace std;

int main()
{
    Graph graph;
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(3);
    graph.addEdge(2,3);
    graph.addEdge(2,3);

    VertexEdges v_edges = graph.inEdges(3);
    for(int i = 0; i < v_edges.num; i++)
    {
        std::cout << "[" << v_edges.edges[i].from <<", " << v_edges.edges[i].to << "]; " << std::endl;
    }
    return 0;
}
