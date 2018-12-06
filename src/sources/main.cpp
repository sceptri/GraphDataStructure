#include <iostream>
#include "graphstructure.h"

using namespace std;

int main()
{
    Graph graph;
    std::cout << "Adding Vertex(2): "<< graph.addVertex(2) << std::endl;
    std::cout << "Adding Vertex(3): "<< graph.addVertex(3) << std::endl;
    std::cout << "Adding Vertex(3): "<< graph.addVertex(3) << std::endl;
    
    std::cout << "Vertex Count: " << graph.getVertexCount() << std::endl;

    std::cout << "Adding Edge1: "<< graph.addEdge(2,3) << std::endl;
    std::cout << "E count: " << graph.getEdgeCount() << std::endl;
    std::cout << "Adding Edge2: "<< graph.addEdge(2,3) << std::endl;
    
    std::cout << "E count: " << graph.getEdgeCount() << std::endl;

    std::cout << "getting inEdges" << std::endl;

    VertexEdges v_edges = graph.inEdges(3);

    std::cout << v_edges.num << std::endl;

    for(int i = 0; i < v_edges.num; i++)
    {
        std::cout << "[" << v_edges.edges[i].from <<", " << v_edges.edges[i].to << "]; " << std::endl;
    }
    return 0;
}
