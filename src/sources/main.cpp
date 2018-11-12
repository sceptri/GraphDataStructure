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
    std::cout << graph.getEdge(1,3).from << std::endl;
    return 0;
}
